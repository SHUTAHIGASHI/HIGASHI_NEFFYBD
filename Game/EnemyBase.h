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
	// 当たり判定チェック
	bool CollisionCheck(Player* pPlayer);
	// 落下処理
	void OnFall();
	// 削除判定
	bool IsDelete() { return m_isDelete; }
private:
	// 画面外に行ったら削除
	void DeleteDisableObject();
	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (EnemyBase::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate();
	void FallDownUpdate();

private:
	// 反射判定
	bool m_isReflection;
	// オブジェクトの削除判定
	bool m_isDelete;
	// 画像ハンドル
	int m_hImg;
	// 画像サイズ
	int m_graphSizeX;
	int m_graphSizeY;
	// 回転方向
	double m_angle;
	// 座標
	VECTOR m_pos;
	VECTOR m_dir;
};

