#include "SceneTitleMenu.h"
#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneOption.h"
#include "SceneHowTo.h"
#include "SceneModeSelect.h"

namespace
{
	// ���P�b�g�̃T�C�Y
	constexpr double kRocketSize = 1.0;
	// ���P�b�g�̉�]���x
	constexpr float kRocketRotaSpeed = 0.0175f;
	// ���P�b�g�̒��S����̋���
	constexpr float kRocketCenterDistance = 280.0f;
	// �^�C�g�����S�`��ʒu
	constexpr float kLogoDrawPosX = Game::kScreenWidthHalf;
	constexpr float kLogoDrawPosY = 220.0f;
	// �e�L�X�g�`��ʒu
	constexpr float kTextDrawPosY = Game::kScreenHeight - 200.0f;
	constexpr float kTextDrawSpace = Game::kFontSize + 10;
	// �I���\���ڂ̐�
	constexpr int kSelectItemNum = 3;
	// �e�L�X�g
	const char* const kTextSceneName = "�Q�[���X�^�[�g";
	const char* const kTextNormal = "�����т���";
	const char* const kTextEndless = "�ݒ�";
	const char* const kTextGameEnd = "�I��";
	const char* const kTextMusicName = "�� VALIS - ���팻�ۃ_���X�_���X";
}

SceneTitleMenu::SceneTitleMenu(SceneManager& manager) : Scene(manager),
m_updateFunc(&SceneTitleMenu::NormalUpdate),
m_countFrame(0),
m_selectedPos(0),
m_selectedItemName(),
m_hTitleLogoImg(-1),
m_hTitleRocketImg(-1),
m_hCrossHairImg(-1),
m_hBgImg(-1),
m_hTitleBgm(-1),
m_rocketPos(),
m_rocketDir(),
m_rocketRotation(DX_PI_F),
m_rocketAngle(90.0)
{
	m_hTitleLogoImg = LoadGraph("Data/ImageData/GAME_TITLE.png");
	m_hTitleRocketImg = LoadGraph("Data/ImageData/sought.png");
	m_hCrossHairImg = LoadGraph("Data/ImageData/crosshair.png");
	m_hBgImg = LoadGraph("Data/ImageData/GameBg.jpg");

	m_musicNameDrawPos = VGet(Game::kScreenWidth, Game::kScreenHeight - 30, 0.0f);
	m_rocketPos = VGet(kLogoDrawPosX, kLogoDrawPosY + kRocketCenterDistance, 0.0f);
	m_rocketDir = VGet(0.0f, 0.0f, 0.0f);
}

SceneTitleMenu::~SceneTitleMenu()
{
	DeleteGraph(m_hTitleLogoImg);
	DeleteGraph(m_hTitleRocketImg);
	DeleteGraph(m_hCrossHairImg);
	DeleteGraph(m_hBgImg);
}

void SceneTitleMenu::Update(const InputState& input)
{
	m_countFrame++;
	(this->*m_updateFunc)(input);
}

void SceneTitleMenu::Draw()
{
	// �w�i�摜
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hBgImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �^�C�g�����S
	DrawRotaGraphF(m_rocketPos.x, m_rocketPos.y, kRocketSize, m_rocketRotation, m_hTitleRocketImg, true);
	// ����
	DrawRotaGraphF(kLogoDrawPosX, kLogoDrawPosY, 0.8, 0, m_hTitleLogoImg, true);
	DrawMenuText();
	// �Ȗ��`��
	SetFontSize(20);
	DrawFormatStringF(m_musicNameDrawPos.x, m_musicNameDrawPos.y, Game::kColorRed, "%s", kTextMusicName);
	SetFontSize(Game::kFontSize);
}

void SceneTitleMenu::UpdateRocket()
{
	// ��]���𖈃t���[���ύX
	m_rocketRotation += kRocketRotaSpeed;
	if (m_rocketRotation > DX_PI_F)
	{
		m_rocketRotation = -DX_PI_F;
	}
	// �p�x�̒l�𑝂₷
	m_rocketAngle += 1.0f;

	// �p�x�̍ő�l(  360��)�𒴂����ꍇ�A0�ɂ���
	if (m_rocketAngle >= 360.0f)
	{
		m_rocketAngle = 0.0f;
	}
	// �p�x�����W�A���ɕϊ�
	float rad = m_rocketAngle * (DX_PI_F / 180.0f);

	// ���S�ʒu���甼�a�����ƂɋO�����v�Z
	m_rocketDir.x = cos(rad) * kRocketCenterDistance;
	m_rocketDir.y = sin(rad) * kRocketCenterDistance;

	// ���S�ʒu�̑��
	m_rocketPos = VGet(kLogoDrawPosX, kLogoDrawPosY, 0.0f);

	// �x�N�g�����ʒu�ɉ��Z
	m_rocketPos = VAdd(m_rocketPos, m_rocketDir);
}

std::string SceneTitleMenu::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextSceneName;
	}
	else if (textNum == 1)
	{
		text = kTextNormal;
	}
	else if (textNum == 2)
	{
		text = kTextEndless;
	}
	else if (textNum == 3)
	{
		text = kTextGameEnd;
	}

	return text;
}

void SceneTitleMenu::DrawMenuText()
{
	int drawX = 0, drawY = static_cast<int>(Game::kScreenHeightHalf);
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tText.c_str()) / 2));
		drawY = static_cast<int>(kTextDrawPosY + (kTextDrawSpace * i));
		DrawFormatString(drawX, drawY, 0xffffff, "%s", tText.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	int textLength = GetDrawFormatStringWidth(m_selectedItemName.c_str());
	drawX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<int>(kTextDrawPosY + (kTextDrawSpace * m_selectedPos));
	DrawFormatString(drawX, drawY, Game::kColorRed, "%s", m_selectedItemName.c_str());

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawRotaGraph(drawX - Game::kFontSize, drawY + 19, 0.4, 0.0, m_hCrossHairImg, true);
		DrawRotaGraph(drawX + textLength + Game::kFontSize, drawY + 19, 0.4, 0.0, m_hCrossHairImg, true, true);
	}
}

void SceneTitleMenu::OnSceneEnd()
{
	if (m_selectedPos == 0)
	{
		m_Manager.ChangeScene(new SceneMain(m_Manager));
	}
	else if (m_selectedPos == 1)
	{
		m_Manager.PushScene(new SceneHowTo(m_Manager));
	}
	else if (m_selectedPos == 2)
	{
		m_Manager.PushScene(new SceneOption(m_Manager));
	}
	else if (m_selectedPos == 3)
	{
		m_Manager.GameEnd();
	}
	return;
}

void SceneTitleMenu::NormalUpdate(const InputState& input)
{
	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = kSelectItemNum;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > kSelectItemNum) m_selectedPos = 0;
	}

	UpdateRocket();

	if (input.IsTriggered(InputType::enter))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);
		OnSceneEnd();
		return;
	}

	m_musicNameDrawPos.x -= 3.0f;
	float textLength = static_cast<float>(GetDrawFormatStringWidth(kTextMusicName));
	if ((m_musicNameDrawPos.x + textLength) < 0.0f)
	{
		m_musicNameDrawPos.x = Game::kScreenWidth;
	}
}
