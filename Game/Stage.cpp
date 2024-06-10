#include "Stage.h"
#include "Game.h"
#include "EnemyManager.h"
#include "SceneMain.h"
#include "Player.h"
#include "MelonCreamSoda.h"

Stage::Stage():
	m_Main(nullptr),
	m_Player(nullptr),
	m_Item(nullptr),
	m_hMelonCreamSodaImg(-1)
{
}

Stage::~Stage()
{
	DeleteGraph(m_hMelonCreamSodaImg);

	delete m_Item;
	m_Item = nullptr;
}

void Stage::Init()
{
	m_hMelonCreamSodaImg = LoadGraph("Data/ImageData/meloncreamsoda.png");
}

void Stage::Update()
{
	if (m_Item != nullptr)
	{
		m_Item->Update();
		if (m_Item->CollisionCheck(m_Player))
		{
			m_Main->OnGameClear();
		}
	}
}

void Stage::Draw()
{
	DrawBox(0, 0, static_cast<int>(Game::kScreenWidth), static_cast<int>(Game::kUpperLimit), 0x000000, true);
	DrawBox(0, static_cast<int>(Game::kLowerLimit), static_cast<int>(Game::kScreenWidth), static_cast<int>(Game::kScreenHeight), 0x000000, true);
	DrawBox(0, static_cast<int>(Game::kUpperLimit) - 1, static_cast<int>(Game::kScreenWidth), static_cast<int>(Game::kUpperLimit) + 1, 0xffffff, true);
	DrawBox(0, static_cast<int>(Game::kLowerLimit) - 1, static_cast<int>(Game::kScreenWidth), static_cast<int>(Game::kLowerLimit) + 1, 0xffffff, true);

	if (m_Item != nullptr)
	{
		m_Item->Draw();
	}
}

void Stage::OnRestart()
{
	if (m_Item != nullptr)
	{
		delete m_Item;
		m_Item = nullptr;
	}
}

void Stage::OnTimeUp()
{
	m_Item = new MelonCreamSoda(m_hMelonCreamSodaImg);
}
