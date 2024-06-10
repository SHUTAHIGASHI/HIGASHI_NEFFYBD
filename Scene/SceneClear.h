#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneClear :
    public Scene
{
public:
    SceneClear(SceneManager& manager);
    virtual ~SceneClear();

    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();

private: // プライベート関数
    // テキスト描画
    void DrawMenuText();
private: // 変数
    // 背景描画座標
    VECTOR m_bgPos;
    // 毎フレームカウント
    int m_countFrame;
    // 背景画像
    int m_hBgImg;
    int m_hClearImg;
    // 画像サイズ
    int m_ClearGraphX;
    int m_ClearGraphY;
    // テキスト描画判定
    bool m_isScrollEnd;
};
