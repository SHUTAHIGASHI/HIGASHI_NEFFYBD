#include "Game.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneDebug.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウモードのサイズ変更
	SetWindowSizeChangeEnableFlag(true);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// リソースの読み込み
	LPCSTR font = Game::kFontFileName;	// 読み込むフォントファイルのパス
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}
	// 標準フォント設定
	ChangeFont("DotGothic16");
	SetFontSize(Game::kFontSize);

	// ゲーム中のマウスポインタ描画設定
	//SetMouseDispFlag(false);

	// サウンドマネージャー宣言
	auto& soundManager = SoundManager::GetInstance();
	// ゲームマネージャー宣言
	auto& gameManager = GameDataManager::GetInstance();
	// キー入力状態クラス宣言
	InputState input;
	// シーンマネージャー宣言
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
		// 音楽再生開始
		if (SoundManager::GetInstance().IsPlayingMusic() != 1)
		{
			SoundManager::GetInstance().PlayMusic(MusicType::main);
		}

		// 画面のクリア
		ClearDrawScreen();

		input.Update();

		// 現在のシーンの更新
		scene.Update(input);

		// 現在のシーンの描画
		scene.Draw();

		// 裏画面を表画面と入れ替える
		ScreenFlip();

		if (scene.IsGameEnd()) break;

#ifdef _DEBUG
		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}

	SetMouseDispFlag(true);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}