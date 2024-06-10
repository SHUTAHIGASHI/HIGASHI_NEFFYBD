#pragma once
#include "Scene.h"
#include <string>

enum class GameMode;

class SceneModeSelect :
    public Scene
{
public:
    SceneModeSelect(SceneManager& manager);
    virtual ~SceneModeSelect();

    void Update(const InputState& input);
    void Draw();

private:
    std::string GetCurrentText(int textNum);
    void DrawMenuText();

private:
    // 毎フレームカウント
    int m_countFrame;
    // 選択したゲームモード
    GameMode m_gameMode;
    // 選択済みの項目
    std::string m_selectedItemName;
    int m_selectedPos;
    // ボード画像ハンドル
    int m_hBoardImg;
};

