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

	// レベルアップ時の処理
	void OnLevelUp();
	// 座標を取得
	VECTOR GetPos() { return m_pos; }
private:
	void SetInitPos();

private:
	// 描画座標
	VECTOR m_pos;
	VECTOR m_dir;
	// 画像ハンドル
	int m_hImg;
	// サイズ
	double m_size;
	// 角度
	double m_angle;
	// 落下判定
	bool m_isFall;
};

