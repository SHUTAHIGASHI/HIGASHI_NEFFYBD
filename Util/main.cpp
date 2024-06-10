#include "Game.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneDebug.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�B���h�E���[�h�̃T�C�Y�ύX
	SetWindowSizeChangeEnableFlag(true);
	// �E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// ���\�[�X�̓ǂݍ���
	LPCSTR font = Game::kFontFileName;	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�ǂݍ��݃G���[����
		MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
	}
	// �W���t�H���g�ݒ�
	ChangeFont("DotGothic16");
	SetFontSize(Game::kFontSize);

	// �Q�[�����̃}�E�X�|�C���^�`��ݒ�
	//SetMouseDispFlag(false);

	// �T�E���h�}�l�[�W���[�錾
	auto& soundManager = SoundManager::GetInstance();
	// �Q�[���}�l�[�W���[�錾
	auto& gameManager = GameDataManager::GetInstance();
	// �L�[���͏�ԃN���X�錾
	InputState input;
	// �V�[���}�l�[�W���[�錾
	SceneManager scene;

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		//SetMousePoint(static_cast<int>(Game::kScreenWidthHalf), static_cast<int>(Game::kScreenHeightHalf));
		// ���y�Đ��J�n
		if (SoundManager::GetInstance().IsPlayingMusic() != 1)
		{
			SoundManager::GetInstance().PlayMusic(MusicType::main);
		}

		// ��ʂ̃N���A
		ClearDrawScreen();

		input.Update();

		// ���݂̃V�[���̍X�V
		scene.Update(input);

		// ���݂̃V�[���̕`��
		scene.Draw();

		// ����ʂ�\��ʂƓ���ւ���
		ScreenFlip();

		if (scene.IsGameEnd()) break;

#ifdef _DEBUG
		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	SetMouseDispFlag(true);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}