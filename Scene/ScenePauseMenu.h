#pragma once
#include "Scene.h"
#include <memory>
#include <string>

class ScenePauseMenu :
    public Scene
{
public:
    ScenePauseMenu(SceneManager& manager);
    virtual ~ScenePauseMenu();

    void Update(const InputState& input);
    void Draw();

private: // プライベート関数
    std::string GetCurrentText(int textNum);
    void DrawMenuText();

private: // 変数
    // 選択中の項目
    int m_selectedPos;
    // 選択中の項目名
    std::string m_selectedItemName;
};

