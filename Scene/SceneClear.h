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

    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();

private: // �v���C�x�[�g�֐�
    // �e�L�X�g�`��
    void DrawMenuText();
private: // �ϐ�
    // �w�i�`����W
    VECTOR m_bgPos;
    // ���t���[���J�E���g
    int m_countFrame;
    // �w�i�摜
    int m_hBgImg;
    int m_hClearImg;
    // �摜�T�C�Y
    int m_ClearGraphX;
    int m_ClearGraphY;
    // �e�L�X�g�`�攻��
    bool m_isScrollEnd;
};
