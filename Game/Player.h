#pragma once
#include "Game.h"

namespace
{
	// �v���C���[�̓����蔻�蒲���l
	constexpr float kCollSize = 9.0f;
}

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player();

	void SetMain(SceneMain* main) { m_pMain = main; }
	// �摜�ݒ�
	void SetPlayerGraph(int handle);

	void Init();
	void Update(const InputState& input);
	void Draw();
	// �Փ˂̔���
	void OnColl();
	// ���W�擾
	VECTOR GetPos() { return m_pos; }
	float GetPosLeft() { return m_pos.x - (m_graphSizeX / 2) + kCollSize; }
	float GetPosRight() { return m_pos.x + (m_graphSizeX / 2) - kCollSize; }
	float GetPosTop() { return m_pos.y - (m_graphSizeY / 2) + kCollSize; }
	float GetPosBottom() { return m_pos.y + (m_graphSizeY / 2) - kCollSize; }
	// �c�@�擾
	int GetPlayerLife() { return m_playerLife; }
	// ��������
	bool IsDead() { return m_isDead; }
private:
	// �L�����N�^�[����
	void ControllUpdate(const InputState& input);

	using m_tUpdateFunc = void (Player::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);
private:
	// ���C���̃|�C���^
	SceneMain* m_pMain;
	// ���W
	VECTOR m_pos;
	std::vector<VECTOR> m_exPos;
	// �摜�n���h��
	int m_hImg;
	// �摜�T�C�Y
	int m_graphSizeX;
	int m_graphSizeY;
	// �v���C���[�c�@
	int m_playerLife;
	// ���G����
	int m_invTime;
	// ���S����
	bool m_isDead;
	// �����ړ�����
	bool m_isFall;
};

