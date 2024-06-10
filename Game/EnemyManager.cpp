#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemySpawner.h"
#include "SceneMain.h"
#include "Player.h"

namespace
{
	// �G�����̒x������
	constexpr int kSpawnDelay = 45;
	// �����S�̊m��
	constexpr int kRingoRate = 75;
}

EnemyManager::EnemyManager():
	m_Player(nullptr),
	m_pMain(nullptr),
	m_pEnemies(),
	m_Rara(),
	m_spawnDelay(0),
	m_currentSoundType(),
	m_currentRingoSoundType(),
	m_hRaraImg(-1),
	m_hChinoImg(-1),
	m_hMyuImg(-1),
	m_hNinaImg(-1),
	m_hVitteImg(-1),
	m_hCurrentImg(-1),
	m_hCurrentRingoImg(-1),
	m_hRingoImg(-1),
	m_hBigringoImg(-1),
	m_isCanShot(false)
{
}

EnemyManager::~EnemyManager()
{
	delete m_Rara;

	DeleteGraph(m_hRaraImg);
	DeleteGraph(m_hChinoImg);
	DeleteGraph(m_hMyuImg);
	DeleteGraph(m_hNinaImg);
	DeleteGraph(m_hVitteImg);
	DeleteGraph(m_hRingoImg);
	DeleteGraph(m_hBigringoImg);
}

void EnemyManager::Init()
{
	// �V���b�g��łĂ��Ԃɂ���
	m_isCanShot = true;
	// �����Ԋu������
	m_spawnDelay = kSpawnDelay;
	// �摜���[�h
	m_hRaraImg = LoadGraph("Data/ImageData/rara.png");
	m_hChinoImg = LoadGraph("Data/ImageData/chino.png");
	m_hMyuImg = LoadGraph("Data/ImageData/myu.png");
	m_hNinaImg = LoadGraph("Data/ImageData/nina.png");
	m_hVitteImg = LoadGraph("Data/ImageData/vitte.png");
	m_hRingoImg = LoadGraph("Data/ImageData/ringo.png");
	m_hBigringoImg = LoadGraph("Data/ImageData/bigringo.png");
	// �摜�Ɖ��̎g�p����f�[�^������
	m_hCurrentRingoImg = m_hRingoImg;
	m_currentRingoSoundType = SoundType::ringo;

	// �G�����I�u�W�F�N�g�̍쐬S
	m_Rara = new EnemySpawner(m_hRaraImg);

	// �G�����I�u�W�F�N�g��������
	m_Rara->Init();
}

void EnemyManager::Update()
{
	m_spawnDelay--;
	if (m_spawnDelay < 0)
	{
		if (m_isCanShot)
		{
			OnSpawnEnemy();
			m_spawnDelay = kSpawnDelay;
		}
	}

	m_Rara->Update();

	for (auto& enemy : m_pEnemies)
	{
		enemy->Update();

		if (enemy->CollisionCheck(m_Player))
		{
			m_Player->OnColl();
		}
	}

	DeleteDisableEnemy();
}

void EnemyManager::Draw()
{
	m_Rara->Draw();

	for (auto& enemy : m_pEnemies)
	{
		enemy->Draw();
	}
}

void EnemyManager::OnGameOver()
{
	m_isCanShot = false;

	for (auto& enemy : m_pEnemies)
	{
		enemy->OnFall();
	}
}

void EnemyManager::OnLevelUp()
{
	m_hCurrentRingoImg = m_hBigringoImg;
	m_currentRingoSoundType = SoundType::ringo2;
	m_Rara->OnLevelUp();
}

void EnemyManager::OnRestart()
{
	m_isCanShot = true;
	m_spawnDelay = kSpawnDelay;
	m_hCurrentRingoImg = m_hRingoImg;
	m_currentRingoSoundType = SoundType::ringo;
	m_Rara->Init();
	m_pEnemies.clear();
}

void EnemyManager::SetRandObject()
{
	int n = GetRand(kRingoRate);
	if (n == 1)
	{
		m_hCurrentImg = m_hChinoImg;
		m_currentSoundType = SoundType::chino;

	}
	else if (n == 2)
	{
		m_hCurrentImg = m_hMyuImg;
		m_currentSoundType = SoundType::myu;
	}
	else if (n == 3)
	{
		m_hCurrentImg = m_hNinaImg;
		m_currentSoundType = SoundType::nina;
	}
	else if (n == 4)
	{
		m_hCurrentImg = m_hVitteImg;
		m_currentSoundType = SoundType::vitte;
	}
	else
	{
		m_hCurrentImg = m_hCurrentRingoImg;
		m_currentSoundType = m_currentRingoSoundType;
	}
}

void EnemyManager::OnSpawnEnemy()
{
	SetRandObject();
	SoundManager::GetInstance().PlaySE(m_currentSoundType);
	m_pEnemies.push_back(std::make_shared<EnemyBase>(m_hCurrentImg, m_Rara->GetPos(), m_Player->GetPos()));
}

void EnemyManager::DeleteDisableEnemy()
{
	for (auto& enemy : m_pEnemies)
	{
		if (enemy->IsDelete())
		{
			m_pMain->OnScoreUp();
		}
	}

	// ���Ȃ��Ȃ����G�͔r��
	auto rmIt = std::remove_if(m_pEnemies.begin(), m_pEnemies.end(),
		[](const std::shared_ptr<EnemyBase>& obj)
		{
			return obj->IsDelete();
		});

	// ���ۂɔ͈͂��w�肵�č폜
	m_pEnemies.erase(rmIt, m_pEnemies.end());
}
