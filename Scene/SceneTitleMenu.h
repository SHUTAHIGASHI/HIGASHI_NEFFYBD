#pragma once
#include "Scene.h"
#include <string>
#include "Game.h"

class SceneTitleMenu :
    public Scene
{
public:
    SceneTitleMenu(SceneManager& manager);
    virtual ~SceneTitleMenu();

    void Update(const InputState& input);
    void Draw();

private: // プライベート関数
    // ロケットの移動処理
    void UpdateRocket();

    // 文字列の更新
    std::string GetCurrentText(int textNum);
    void DrawMenuText();

    // タイトル終了時処理
    void OnSceneEnd();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // タイトル画面更新処理
    void NormalUpdate(const InputState& input);

private: // シーン全体の管理変数
    // 毎フレームカウント用
    int m_countFrame;

private: // シーン装飾の管理変数
    // 曲名表示位置
    VECTOR m_musicNameDrawPos;    
    // 選択中の項目
    int m_selectedPos;
    // 選択中の項目名
    std::string m_selectedItemName;
    // 画像ハンドル
    int m_hTitleLogoImg;
    int m_hTitleRocketImg;
    int m_hCrossHairImg;
    int m_hBgImg;
    // タイトルBGMハンドル
    int m_hTitleBgm;

private: // ロケット動く処理の変数達
    // タイトル画面のロケット位置
    VECTOR m_rocketPos;
    VECTOR m_rocketDir;
    double m_rocketRotation;
    float m_rocketAngle;
};

