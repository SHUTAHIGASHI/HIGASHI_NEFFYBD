#include "Player.h"
#include "SceneMain.h"

namespace
{
	// �v���C���[��{�ړ����x
	constexpr float kMoveSpeed = 10.0f;
	// ���S�ɖ߂�Ƃ��̑��x
	constexpr float kReturnSpeed = 4.0f;
	// ���G����
	constexpr int kInvTime = 60 * 2;
	// �c�@�ő�l
	constexpr int kLifeMax = 3;
	// �c�����c���t���[����
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
	// �O���t�T�C�Y�擾
	GetGraphSize(m_hImg, &m_graphSizeX, &m_graphSizeY);
}

void Player::Init()
{
	// �������W
	m_pos = VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f);
	// �c�@�ő�l
	m_playerLife = kLifeMax;
	// ���G���ԏ�����
	m_invTime = 0;
	// �ϐ�������
	m_isFall = true;
	// ���S���菉����
	m_isDead = false;
}

void Player::Update(const InputState& input)
{
	//�X�V�����̃����o�֐��|�C���^
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
		// �c�@��0�̎��ŏ�����
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

	// �㉺����
	if (m_pos.y < Game::kUpperLimit) m_isFall = true;
	else if (m_pos.y > Game::kLowerLimit) m_isFall = false;
	ControllUpdate(input);
}