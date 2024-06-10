#pragma once

#include <DxLib.h>
#include "InputState.h"
#include "SoundManager.h"
#include "GameDataManager.h"

namespace Game
{
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = true;
#endif

	// ウィンドウ名
	const char* const kTitleText = "ﾊｯﾋﾟｰﾊﾞｰｽﾃﾞｰﾈﾌｨ=ｻｰﾝ!!";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// ゲームで使う色コード
	constexpr int kColorRed = 0xba4359;
	constexpr int kColorPurple = 0x7a4976;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;

	/* フォント */
	// フォントファイル
	const char* const kFontFileName = "Data/fontData/DotGothic16-Regular.ttf";
	// フォントサイズ
	constexpr int kFontSize = 30;

	// カラーモード
	constexpr int kColorDepth = 32;
	
	// ゲームの基本設定 //
	constexpr int kBoostLevelMax = 3;
	// プレイヤーの基本設定
	constexpr float kChipSize = 32.0f;

	// 基本移動速度
	constexpr float kMoveSpeed = 12.0f;

	// ゲームのステージサイズ
	constexpr float kUpperLimit = 150.0f;
	constexpr float kLowerLimit = Game::kScreenHeight - kUpperLimit;
}