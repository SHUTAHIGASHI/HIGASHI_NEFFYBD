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
    // ���t���[���J�E���g
    int m_countFrame;
    // �I�������Q�[�����[�h
    GameMode m_gameMode;
    // �I���ς݂̍���
    std::string m_selectedItemName;
    int m_selectedPos;
    // �{�[�h�摜�n���h��
    int m_hBoardImg;
};

