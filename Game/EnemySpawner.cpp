#include "EnemySpawner.h"
#include "EnemyBase.h"

namespace
{
	constexpr float kFallSpeed = 6.0f;
	// 背景基本移動速度
	constexpr float kMoveSpeed = 6.0f;
}

EnemySpawner::EnemySpawner(int handle):
	m_pos(),
	m_dir(),
	m_hImg(handle),
	m_size(1.0),
	m_angle(0.0),
	m_isFall(false)
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Init()
{
	// 落下判定初期化
	m_isFall = true;
	// 座標初期化
	SetInitPos();
	// サイズ初期化
	m_size = 1.0;
}

void EnemySpawner::Update()
{
	if (m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_dir.x *= -1;
	}

	if (m_pos.y < Game::kUpperLimit || m_pos.y > Game::kLowerLimit)
	{
		m_dir.y *= -1;
	}

	if (VSize(m_dir) > 0) m_dir = VNorm(m_dir);
	m_dir = VScale(m_dir, kMoveSpeed);
	m_pos = VAdd(m_pos, m_dir);
}

void EnemySpawner::Draw()
{
	DrawRotaGraphF(m_pos.x, m_pos.y, m_size, m_angle, m_hImg, true);
}

void EnemySpawner::OnLevelUp()
{
	m_size *= 2;
}

void EnemySpawner::SetInitPos()
{
	m_pos = VGet(Game::kScreenWidthHalf, Game::kLowerLimit, 0.0f);
	float dirX = static_cast<float>(GetRand(1));
	if (dirX == 0) dirX = -1;
	float dirY = static_cast<float>(GetRand(1));
	if (dirY == 0) dirY = -1;
	m_dir = VGet(dirX, dirY, 0.0f);
}
