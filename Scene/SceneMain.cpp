#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneModeSelect.h"
#include "ScenePauseMenu.h"
#include "SceneGameOver.h"
#include "SceneClear.h"
#include "SceneFade.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CommentSystem.h"
#include <string>

namespace
{
	// �Q�[������
	constexpr int kGameTimeMax = 1800;
	// �Q�[���x��
	constexpr int kRestartDelay = 180;
	constexpr int kClearedDelay = 120;
	// ��ʗh��̑傫��
	constexpr int kQuakeScale = 30;
}

SceneMain::SceneMain(SceneManager& manager) : 
	Scene(manager),
	m_updateFunc(&SceneMain::SceneStartUpdate),
	m_drawFunc(&SceneMain::NormalDraw),
	m_pStage(std::make_shared<Stage>()),
	m_pPlayer(std::make_shared<Player>()),
	m_pEnemy(std::make_shared<EnemyManager>()),
	m_pComment(std::make_shared<CommentSystem>()),
	m_isModeSelected(false),
	m_currentGameMode(GameMode::empty),
	m_countFrame(0),
	m_delayTime(0)
{
	this->Init();
}

SceneMain::~SceneMain()
{
	// ����������폜
	DeleteGraph(m_hNeffyImg);
	DeleteGraph(m_hBgImg);
}

void SceneMain::Init()
{
	// �w�i�摜�Ǎ�
	m_hNeffyImg = LoadGraph("Data/ImageData/neffy.png");
	m_hBgImg = LoadGraph("Data/ImageData/GameBg.jpg");
	// ��ʗh��̑傫��������
	m_quakeScale = 0;
	// �Q�[�����ԏ�����
	m_gameTime = kGameTimeMax;
	// �e�L�X�g�J���[������
	m_countTextColor = Game::kColorWhite;

	// �X�e�[�W������
	m_pStage->SetMain(this);
	m_pStage->SetPlayer(m_pPlayer.get());
	m_pStage->Init();
	// �v���C���[�̏�����
	m_pPlayer->SetMain(this);
	m_pPlayer->SetPlayerGraph(m_hNeffyImg);
	m_pPlayer->Init();
	// �G�l�~�[�N���X�̏�����
	m_pEnemy->SetPlayer(m_pPlayer.get());
	m_pEnemy->SetMain(this);
	m_pEnemy->Init();
	// �R�����g�`��N���X�̏�����
	m_pComment->Init();
}

void SceneMain::Update(const InputState& input)
{
	m_countFrame++;

	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}
#ifdef _DEBUG
	if (input.IsTriggered(InputType::space))
	{
		m_gameTime -= 600;
		m_gameScore += 100;
	}
#endif
	ChangeTextColor();

	//�X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)(input);

	if (m_quakeScale != 0)
	{
		m_quakeScale *= -1;
		if (m_quakeScale < 0)m_quakeScale++;
		else if (m_quakeScale > 0)m_quakeScale--;
	}
	else
	{
		DeleteGraph(m_hQuakeScreen);
		m_drawFunc = &SceneMain::NormalDraw;
	}

	m_pComment->Update();
}

void SceneMain::Draw()
{
	// �w�i�摜
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hBgImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�`�揈���̃����o�֐��|�C���^
	(this->*m_drawFunc)();
	
	// �R�����g
	m_pComment->Draw();
}

void SceneMain::OnScoreUp()
{
	m_gameScore++;
}

void SceneMain::OnDamage()
{
	m_hQuakeScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	m_quakeScale = kQuakeScale;
	m_drawFunc = &SceneMain::QuakeDraw;
}

void SceneMain::OnGameOver()
{
	if (m_currentGameMode == GameMode::normal)
	{
		m_delayTime = kRestartDelay;
		m_pComment->OnGameOver();
		m_pEnemy->OnGameOver();
	}
	else if (m_currentGameMode == GameMode::endless)
	{
		GameDataManager::GetInstance().SetGameScore(m_gameScore);
		m_Manager.PushScene(new SceneGameOver(m_Manager));
	}
	m_updateFunc = &SceneMain::GameOverUpdate;
}

void SceneMain::OnGameClear()
{
	SoundManager::GetInstance().PlaySE(SoundType::raraty);
	m_delayTime = kClearedDelay;
	m_updateFunc = &SceneMain::GameClearUpdate;
}

void SceneMain::OnRestart()
{
	m_gameTime = kGameTimeMax;
	m_gameScore = 0;
	m_pStage->OnRestart();
	m_pEnemy->OnRestart();
	m_pPlayer->Init();
	ChangeUpdateMode();
}

void SceneMain::OnTimeUp()
{
	m_pStage->OnTimeUp();
}

void SceneMain::ChangeTextColor()
{
	if (m_gameTime < 60 * 10)
	{
		m_countTextColor = Game::kColorRed;
	}
	else
	{
		m_countTextColor = Game::kColorWhite;
	}
}

void SceneMain::DrawPlayerLife()
{
	float drawX = 75.0f, drawY = 40.0f;
	DrawFormatStringF(drawX, drawY, 0xffffff, "�c�̨ : %d", m_pPlayer->GetPlayerLife());

	int drawSpace = 50;
	drawX = 100.0f, drawY = 100.0f;
	for (int i = 0; i < m_pPlayer->GetPlayerLife(); i++)
	{
		DrawRotaGraphF(drawX + (i * drawSpace), drawY, 1.0, 0.0, m_hNeffyImg, true);
	}
}

void SceneMain::DrawGameInfo()
{
	// �������Ԃ̃^�C�}�[�`��
	if (m_currentGameMode == GameMode::normal)
	{
		if (m_pPlayer->IsDead())
		{
			std::string text = "�����l�ɋt�炦�Ȃ�����...";
			float stringLength = static_cast<float>(GetDrawFormatStringWidth(text.c_str()) / 2);
			DrawFormatStringF(Game::kScreenWidthHalf - stringLength, Game::kScreenHeight - 100.0f, 0xffffff, "%s", text.c_str());
		}
		else if (m_gameTime > 0)
		{
			SetFontSize(40);
			DrawFormatStringF(Game::kScreenWidthHalf, Game::kScreenHeight - 100.0f, m_countTextColor, "%2d", m_gameTime / 60);
			DrawFormatStringF(Game::kScreenWidthHalf - 100.0f, Game::kScreenHeight - 100.0f, 0xffffff, "�c��");
			DrawFormatStringF(Game::kScreenWidthHalf + 60.0f, Game::kScreenHeight - 100.0f, 0xffffff, "�b�I");
			SetFontSize(Game::kFontSize);
		}
		else
		{
			std::string text = "�������N���[���\�[�_�����I";
			float stringLength = static_cast<float>(GetDrawFormatStringWidth(text.c_str()) / 2);
			DrawFormatStringF(Game::kScreenWidthHalf - stringLength, Game::kScreenHeight - 100.0f, 0xffffff, "%s", text.c_str());
		}
	}
	else if (m_currentGameMode == GameMode::endless)
	{
		SetFontSize(40);
		DrawFormatStringF(Game::kScreenWidthHalf - 195, Game::kScreenHeight - 100.0f, 0xffffff, "��������� %3d ��", m_gameScore);
		SetFontSize(Game::kFontSize);
	}
}

void SceneMain::ChangeUpdateMode()
{
	if (m_currentGameMode == GameMode::normal)
	{
		m_updateFunc = &SceneMain::NormalModeUpdate;
	}
	else if (m_currentGameMode == GameMode::endless)
	{
		m_updateFunc = &SceneMain::EndlessModeUpdate;
	}
}

void SceneMain::SceneStartUpdate(const InputState& input)
{
	if (!m_isModeSelected)
	{
		m_Manager.PushScene(new SceneModeSelect(m_Manager));
		m_isModeSelected = true;
	}
	else
	{
		m_currentGameMode = GameDataManager::GetInstance().GetGameMode();
		ChangeUpdateMode();
	}
}

void SceneMain::NormalModeUpdate(const InputState& input)
{
	m_gameTime--;
	if (m_gameTime <= 0)
	{
		m_gameTime = 0;
		OnTimeUp();
	}

	if (m_gameTime == 60 * 10)
	{
		m_pEnemy->OnLevelUp();
	}

	m_pStage->Update();
	m_pEnemy->Update();
	m_pPlayer->Update(input);
}

void SceneMain::EndlessModeUpdate(const InputState& input)
{
	m_pStage->Update();
	m_pEnemy->Update();
	m_pPlayer->Update(input);
}

void SceneMain::GameOverUpdate(const InputState& input)
{
	m_delayTime--;
	if (m_delayTime <= 0)
	{
		ChangeUpdateMode();
		OnRestart();
	}

	m_pEnemy->Update();
}

void SceneMain::GameClearUpdate(const InputState& input)
{
	m_delayTime--;
	if (m_delayTime <= 0)
	{
		// �N���A��̃V�[�����s
		m_Manager.ChangeScene(new SceneClear(m_Manager));
	}
}

void SceneMain::NormalDraw()
{
	// �X�e�[�W�`��
	m_pStage->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	// �G�l�~�[�`��
	m_pEnemy->Draw();
	// HP
	DrawPlayerLife();
	// �Q�[�����
	DrawGameInfo();
}

void SceneMain::QuakeDraw()
{
	SetDrawScreen(m_hQuakeScreen);
	ClearDrawScreen();
	// �X�e�[�W�`��
	m_pEnemy->Draw();
	// �X�e�[�W�`��
	m_pStage->Draw();
	// �v���C���[�`��
	m_pPlayer->Draw();
	// HP
	DrawPlayerLife();
	// �Q�[�����
	DrawGameInfo();

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(m_quakeScale, m_quakeScale, m_hQuakeScreen, true);
}
