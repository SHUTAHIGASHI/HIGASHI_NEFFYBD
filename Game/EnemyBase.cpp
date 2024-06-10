#include "EnemyBase.h"
#include "Player.h"

namespace
{
	// 基本移動速度
	constexpr float kMoveSpeed = 12.0f;
}

EnemyBase::EnemyBase(int handle, VECTOR pos, VECTOR playerPos):
	m_updateFunc(&EnemyBase::NormalUpdate),
	m_isReflection(false),
	m_isDelete(false),
	m_hImg(handle),
	m_graphSizeX(),
	m_graphSizeY(),
	m_angle(0.0),
	m_pos(pos),
	m_dir()
{
	GetGraphSize(m_hImg, &m_graphSizeX, &m_graphSizeY);

	m_dir = VSub(playerPos, pos);
	if (VSize(m_dir) > 0) m_dir = VNorm(m_dir);
	m_dir = VScale(m_dir, kMoveSpeed);
}

EnemyBase::~EnemyBase()
{
	m_hImg = NULL;
}

void EnemyBase::Update()
{
	//更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)();

	// 不要になったオブジェクトを判定する
	DeleteDisableObject();
}

void EnemyBase::Draw()
{
	DrawRotaGraphF(m_pos.x, m_pos.y, 1.0f, m_angle, m_hImg, true);
}

void EnemyBase::DeleteDisableObject()
{
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isDelete = true;
	}
}

void EnemyBase::NormalUpdate()
{
	if (!m_isReflection)
	{
		if (m_pos.y < Game::kUpperLimit)
		{
			if (m_dir.y < 0)
			{
				m_dir.y *= -1;
				m_isReflection = true;
			}
		}
		else if (m_pos.y > Game::kLowerLimit)
		{
			if (m_dir.y > 0)
			{
				m_dir.y *= -1;
				m_isReflection = true;
			}
		}
	}

	m_pos = VAdd(m_pos, m_dir);
}

void EnemyBase::FallDownUpdate()
{
	m_dir = VGet(0.0f, 1.0f, 0.0f);
	if (VSize(m_dir) > 0) m_dir = VNorm(m_dir);
	m_dir = VScale(m_dir, kMoveSpeed);
	m_pos = VAdd(m_pos, m_dir);
}

bool EnemyBase::CollisionCheck(Player* pPlayer)
{
	// もし当たっていたら
	if (m_pos.x + (m_graphSizeX / 2) > pPlayer->GetPosLeft() &&
		pPlayer->GetPosRight() > m_pos.x - (m_graphSizeX / 2) &&
		m_pos.y + (m_graphSizeY / 2) > pPlayer->GetPosTop() &&
		pPlayer->GetPosBottom() > m_pos.y - (m_graphSizeY / 2))
	{
		return true;
	}

	return false;
}

void EnemyBase::OnFall()
{
	m_updateFunc = &EnemyBase::FallDownUpdate;
}
