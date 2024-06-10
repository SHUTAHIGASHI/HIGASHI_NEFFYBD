#include "Player.h"
#include "SceneMain.h"

namespace
{
	// プレイヤー基本移動速度
	constexpr float kMoveSpeed = 10.0f;
	// 中心に戻るときの速度
	constexpr float kReturnSpeed = 4.0f;
	// 無敵時間
	constexpr int kInvTime = 60 * 2;
	// 残機最大値
	constexpr int kLifeMax = 3;
	// 残像を残すフレーム数
	constexpr int kExPosMax = 5;
}

Player::Player():
	m_updateFunc(&Player::NormalUpdate),
	m_pMain(nullptr),
	m_pos(),
	m_hImg(-1),
	m_graphSizeX(0),
	m_graphSizeY(0),
	m_playerLife(0),
	m_invTime(0),
	m_isDead(false),
	m_isFall(false)
{
}

Player::~Player()
{
}

void Player::SetPlayerGraph(int handle)
{
	m_hImg = handle;
	// グラフサイズ取得
	GetGraphSize(m_hImg, &m_graphSizeX, &m_graphSizeY);
}

void Player::Init()
{
	// 初期座標
	m_pos = VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f);
	// 残機最大値
	m_playerLife = kLifeMax;
	// 無敵時間初期化
	m_invTime = 0;
	// 変数初期化
	m_isFall = true;
	// 死亡判定初期化
	m_isDead = false;
}

void Player::Update(const InputState& input)
{
	//更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);

	m_exPos.push_back(m_pos);
	if (m_exPos.size() > kExPosMax)
	{
		m_exPos.erase(m_exPos.begin());
	}
}

void Player::Draw()
{
	if (!m_isDead) 
	{
		if ((m_invTime / 10) % 4 != 1)
		{
			DrawRotaGraphF(m_pos.x, m_pos.y, 1.0f, 0.0f, m_hImg, true, false, !m_isFall);
			for (auto& exPos : m_exPos)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
				DrawRotaGraphF(exPos.x, exPos.y, 1.0f, 0.0f, m_hImg, true, false, !m_isFall);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void Player::OnColl()
{
	if (m_invTime <= 0)
	{
		m_invTime = kInvTime;
		m_playerLife--;
		// 残機が0の時最初から
		if (m_playerLife <= 0)
		{
			SoundManager::GetInstance().PlaySE(SoundType::dead);
			m_pMain->OnGameOver();
			m_isDead = true;
		}
		else
		{
			SoundManager::GetInstance().PlaySE(SoundType::damage);
			m_pMain->OnDamage();
		}
	}
}

void Player::ControllUpdate(const InputState& input)
{
	if (input.IsTriggered(InputType::boost))
	{
		OnColl();
	}

	if (input.IsPressed(InputType::right))
	{
		m_pos.x += kMoveSpeed;
	}
	if (input.IsPressed(InputType::left))
	{
		m_pos.x -= kMoveSpeed;
	}

	if (m_pos.x < 0)
	{
		m_pos.x = Game::kScreenWidth;
	}
	else if (m_pos.x > Game::kScreenWidth)
	{
		m_pos.x = 0.0f;
	}

	if (m_isFall)
	{
		m_pos.y += kMoveSpeed;
	}
	else if (!m_isFall)
	{
		m_pos.y -= kMoveSpeed;
	}
}

void Player::NormalUpdate(const InputState& input)
{
	if (m_invTime > 0) m_invTime--;

	// 上下判定
	if (m_pos.y < Game::kUpperLimit) m_isFall = true;
	else if (m_pos.y > Game::kLowerLimit) m_isFall = false;
	ControllUpdate(input);
}