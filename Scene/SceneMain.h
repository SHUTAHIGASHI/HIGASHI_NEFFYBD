#pragma once
#include "Scene.h"
#include <memory>

class Player;
class Stage;
class EnemyManager;
class CommentSystem;

enum class GameMode;

class SceneMain :
    public Scene
{
public:
    // コンストラクタ
    SceneMain(SceneManager& manager);
    // デストラクタ
    virtual ~SceneMain();

    // シーン初期化
    void Init();
    // 更新処理
    void Update(const InputState& input);
    // 描画処理
    void Draw();
    // スコア増加
    void OnScoreUp();
    // 被ダメージ処理
    void OnDamage();
    // ゲームオーバー時の処理
    void OnGameOver();
    // ゲームクリア時の処理
    void OnGameClear();
    // 再スタート時の処理
    void OnRestart();
private:
    // ゲームタイムが0になった時の処理
    void OnTimeUp();
    // テキストカラー管理
    void ChangeTextColor();
    // 残機描画
    void DrawPlayerLife();
    // タイム情報表示
    void DrawGameInfo();
    // モードごとに更新処理切り替え
    void ChangeUpdateMode();

    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void SceneStartUpdate(const InputState& input);
    void NormalModeUpdate(const InputState& input);
    void EndlessModeUpdate(const InputState& input);
    void GameOverUpdate(const InputState& input);
    void GameClearUpdate(const InputState& input);

    // メンバ関数ポインタ(更新)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();
    void QuakeDraw();
private:
    std::shared_ptr<Stage> m_pStage;     // ステージ
    std::shared_ptr<Player> m_pPlayer;   // プレイヤー
    std::shared_ptr<EnemyManager> m_pEnemy;   // プレイヤー
    std::shared_ptr<CommentSystem> m_pComment;   // コメントシステム
private:
    // 難易度選択判定
    bool m_isModeSelected;
    // 現在のゲームモード
    GameMode m_currentGameMode;
    // 毎フレームカウント
    int m_countFrame;
    // リスタートまでの時間
    int m_delayTime;
    // 背景ハンドル
    int m_hNeffyImg;
    int m_hBgImg;
    // 画面揺れスクリーン
    int m_hQuakeScreen;
    // 画面揺れの大きさ
    int m_quakeScale;
    // ゲーム時間
    int m_gameTime;
    // ゲームスコア
    int m_gameScore;
    // カウントダウンテキストカラー
    int m_countTextColor;
};

