#pragma once
#include "Game.h"

class Player;

class EnemyBase
{
public:
	EnemyBase(int handle, VECTOR pos, VECTOR playerPos);
	virtual ~EnemyBase();

	void Update();
	void Draw();
	// �����蔻��`�F�b�N
	bool CollisionCheck(Player* pPlayer);
	// ��������
	void OnFall();
	// �폜����
	bool IsDelete() { return m_isDelete; }
private:
	// ��ʊO�ɍs������폜
	void DeleteDisableObject();
	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (EnemyBase::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate();
	void FallDownUpdate();

private:
	// ���˔���
	bool m_isReflection;
	// �I�u�W�F�N�g�̍폜����
	bool m_isDelete;
	// �摜�n���h��
	int m_hImg;
	// �摜�T�C�Y
	int m_graphSizeX;
	int m_graphSizeY;
	// ��]����
	double m_angle;
	// ���W
	VECTOR m_pos;
	VECTOR m_dir;
};

