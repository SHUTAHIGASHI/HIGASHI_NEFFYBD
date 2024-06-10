#include "GameDataManager.h"

GameDataManager::~GameDataManager()
{
}

GameDataManager::GameDataManager():
	m_gameMode(GameMode::normal),
	m_gameScore(0)
{
}