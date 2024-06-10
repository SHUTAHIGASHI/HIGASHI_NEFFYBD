#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace Game
{
	// �V�X�e����{�ݒ� //
#ifdef _DEBUG
	// �E�B���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = true;
#endif

	// �E�B���h�E��
	const char* const kTitleText = "ʯ�߰�ް��ް�̨=���!!";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// �Q�[���Ŏg���F�R�[�h
	constexpr int kColorRed = 0xba4359;
	constexpr int kColorPurple = 0x7a4976;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;

	/* �t�H���g */
	// �t�H���g�t�@�C��
	const char* const kFontFileName = "Data/fontData/DotGothic16-Regular.ttf";
	// �t�H���g�T�C�Y
	constexpr int kFontSize = 30;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// �Q�[���̊�{�ݒ� //
	constexpr int kBoostLevelMax = 3;
	// �v���C���[�̊�{�ݒ�
	constexpr float kChipSize = 32.0f;

	// ��{�ړ����x
	constexpr float kMoveSpeed = 12.0f;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr float kUpperLimit = 150.0f;
	constexpr float kLowerLimit = Game::kScreenHeight - kUpperLimit;
}