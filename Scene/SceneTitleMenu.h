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

private: // �v���C�x�[�g�֐�
    // ���P�b�g�̈ړ�����
    void UpdateRocket();

    // ������̍X�V
    std::string GetCurrentText(int textNum);
    void DrawMenuText();

    // �^�C�g���I��������
    void OnSceneEnd();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �^�C�g����ʍX�V����
    void NormalUpdate(const InputState& input);

private: // �V�[���S�̂̊Ǘ��ϐ�
    // ���t���[���J�E���g�p
    int m_countFrame;

private: // �V�[�������̊Ǘ��ϐ�
    // �Ȗ��\���ʒu
    VECTOR m_musicNameDrawPos;    
    // �I�𒆂̍���
    int m_selectedPos;
    // �I�𒆂̍��ږ�
    std::string m_selectedItemName;
    // �摜�n���h��
    int m_hTitleLogoImg;
    int m_hTitleRocketImg;
    int m_hCrossHairImg;
    int m_hBgImg;
    // �^�C�g��BGM�n���h��
    int m_hTitleBgm;

private: // ���P�b�g���������̕ϐ��B
    // �^�C�g����ʂ̃��P�b�g�ʒu
    VECTOR m_rocketPos;
    VECTOR m_rocketDir;
    double m_rocketRotation;
    float m_rocketAngle;
};

