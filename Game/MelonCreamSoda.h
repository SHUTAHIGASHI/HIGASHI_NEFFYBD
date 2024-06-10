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
	
	// 当たり判定
	bool CollisionCheck(Player* pPlayer);
private:
	// 画像データ
	int m_hImg;
	// 描画座標
	VECTOR m_pos;
	// 画像サイズ
	int m_graphSizeX;
	int m_graphSizeY;
	// サイズ
	double m_size;
	// 角度
	double m_angle;
	// 回転方向
	bool m_rotaRight;
};

