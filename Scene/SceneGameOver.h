#pragma once
#include "Scene.h"
#include <string>
#include "Game.h"

class SceneGameOver :
	public Scene
{
public:
	SceneGameOver(SceneManager& manager);
	virtual ~SceneGameOver();

	void Update(const InputState& input);
	void Draw();

private:
	// �e�L�X�g�`��
	void DrawMenuText();
	// �w�肵���e�L�X�g��Ԃ�
	std::string GetCurrentText(int n);

	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (SceneGameOver::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);
	void SceneStartUpdate(const InputState& input);

private:
	// �t�F�[�h���l
	int m_fadeNum;
	// �t�F�[�h��������
	bool m_isFadeEnd;
	// �Q�[���I�[�o�[�E�B���h�E�̕`����W
	float m_windowDrawPosX;
	float m_windowDrawPosY;
	// �I�𒆂̍���
	int m_selectedPos;
	// �I�𒆂̍��ږ�
	std::string m_selectedItemName;
};

