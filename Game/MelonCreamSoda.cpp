#include "MelonCreamSoda.h"
#include "Player.h"

MelonCreamSoda::MelonCreamSoda(int handle):
	m_hImg(handle),
	m_pos(),
	m_graphSizeX(),
	m_graphSizeY(),
	m_size(1.0),
	m_angle(0.0),
	m_rotaRight(false)
{
	m_pos = VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f);
	GetGraphSize(m_hImg, &m_graphSizeX, &m_graphSizeY);
}

MelonCreamSoda::~MelonCreamSoda()
{
}

void MelonCreamSoda::Update()
{
	if (m_angle > DX_PI / 4)
	{
		m_rotaRight = false;
	}
	else if (m_angle < -DX_PI / 4)
	{
		m_rotaRight = true;
	}

	if (m_rotaRight)
	{
		m_angle += 0.05;
	}
	else
	{
		m_angle -= 0.05;
	}
}

void MelonCreamSoda::Draw()
{
	DrawRotaGraphF(m_pos.x, m_pos.y, m_size, m_angle, m_hImg, true);
}

bool MelonCreamSoda::CollisionCheck(Player* pPlayer)
{
	// ‚à‚µ“–‚½‚Á‚Ä‚¢‚½‚ç
	if (m_pos.x + (m_graphSizeX / 2) > pPlayer->GetPosLeft() &&
		pPlayer->GetPosRight() > m_pos.x - (m_graphSizeX / 2) &&
		m_pos.y + (m_graphSizeY / 2) > pPlayer->GetPosTop() &&
		pPlayer->GetPosBottom() > m_pos.y - (m_graphSizeY / 2))
	{
		return true;
	}

	return false;
}
