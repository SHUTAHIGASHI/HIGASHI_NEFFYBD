#pragma once
#include "Game.h"

class Player;

class MelonCreamSoda
{
public:
	MelonCreamSoda(int handle);
	virtual ~MelonCreamSoda();

	void Update();
	void Draw();
	
	// �����蔻��
	bool CollisionCheck(Player* pPlayer);
private:
	// �摜�f�[�^
	int m_hImg;
	// �`����W
	VECTOR m_pos;
	// �摜�T�C�Y
	int m_graphSizeX;
	int m_graphSizeY;
	// �T�C�Y
	double m_size;
	// �p�x
	double m_angle;
	// ��]����
	bool m_rotaRight;
};

