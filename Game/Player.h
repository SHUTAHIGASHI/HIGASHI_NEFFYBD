#pragma once
#include "Game.h"

namespace
{
	// プレイヤーの当たり判定調整値
	constexpr float kCollSize = 9.0f;
}

class SceneMain;

class Player
{
public:
	Player();
	virtual ~Player();

	void SetMain(SceneMain* main) { m_pMain = main; }
	// 画像設定
	void SetPlayerGraph(int handle);

	void Init();
	void Update(const InputState& input);
	void Draw();
	// 衝突の判定
	void OnColl();
	// 座標取得
	VECTOR GetPos() { return m_pos; }
	float GetPosLeft() { return m_pos.x - (m_graphSizeX / 2) + kCollSize; }
	float GetPosRight() { return m_pos.x + (m_graphSizeX / 2) - kCollSize; }
	float GetPosTop() { return m_pos.y - (m_graphSizeY / 2) + kCollSize; }
	float GetPosBottom() { return m_pos.y + (m_graphSizeY / 2) - kCollSize; }
	// 残機取得
	int GetPlayerLife() { return m_playerLife; }
	// 生存判定
	bool IsDead() { return m_isDead; }
private:
	// キャラクター操作
	void ControllUpdate(const InputState& input);

	using m_tUpdateFunc = void (Player::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);
private:
	// メインのポインタ
	SceneMain* m_pMain;
	// 座標
	VECTOR m_pos;
	std::vector<VECTOR> m_exPos;
	// 画像ハンドル
	int m_hImg;
	// 画像サイズ
	int m_graphSizeX;
	int m_graphSizeY;
	// プレイヤー残機
	int m_playerLife;
	// 無敵時間
	int m_invTime;
	// 死亡判定
	bool m_isDead;
	// 落下移動判定
	bool m_isFall;
};

