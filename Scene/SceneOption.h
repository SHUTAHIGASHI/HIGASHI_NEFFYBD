#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>

enum class volume
{
    SE,
    BGM
};

class SceneOption :
    public Scene
{
public:
    SceneOption(SceneManager& manager);
    virtual ~SceneOption();

    // ������
    void Init();
    // �X�V
    void Update(const InputState& input);
    // �`��
    void Draw();

private: // �v���C�x�[�g�֐�
    // ���ʂ̐ݒ�
    void ChangeVolume(const InputState& input, int& vol);
    // �ύX�������ʏ��𔽉f������
    void SetVolumeInfo();
    // �e�L�X�g�`��ʒu
    void DrawSoundBar();
    // �e�L�X�g���̕`��
    void DrawMenuText();
    // �I�𒆂̕������Ԃ�
    std::string GetCurrentText(int textNum);
private:
    // ����
    int m_volumeBGM;
    int m_volumeSE;
    // �I���ʒu
    int m_selectedPos;
    std::string m_selectedItemName;
};
