#pragma once
#include "Game.h"
#include <memory>

class EnemyBase;

class EnemySpawner
{
public:
	EnemySpawner(int handle);
	virtual ~EnemySpawner();

	void Init();
	void Update();
	void Draw();

	// ���x���A�b�v���̏���
	void OnLevelUp();
	// ���W���擾
	VECTOR GetPos() { return m_pos; }
private:
	void SetInitPos();

private:
	// �`����W
	VECTOR m_pos;
	VECTOR m_dir;
	// �摜�n���h��
	int m_hImg;
	// �T�C�Y
	double m_size;
	// �p�x
	double m_angle;
	// ��������
	bool m_isFall;
};

