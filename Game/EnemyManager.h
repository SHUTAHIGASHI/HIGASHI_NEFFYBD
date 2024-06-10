#pragma once
#include <vector>
#include <memory>
#include "Game.h"

class SceneMain;
class Player;
class EnemyBase;
class EnemySpawner;
class EnemyTurret;

class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void SetPlayer(Player* player) { m_Player = player; }
	void SetMain(SceneMain* main) { m_pMain = main; }

	void Init();
	void Update();
	void Draw();

	void OnGameOver();
	// ���x���A�b�v
	void OnLevelUp();
	// �ăX�^�[�g�̏���
	void OnRestart();
private:
	// �e�����_������
	void SetRandObject();
	// �G��������
	void OnSpawnEnemy();
	// �s�v�ȓG���폜����
	void DeleteDisableEnemy();

private:
	Player* m_Player;
	SceneMain* m_pMain;
	// �G�z��
	std::vector<std::shared_ptr<EnemyBase>> m_pEnemies;
	EnemySpawner* m_Rara;
	// �G�̐����Ԋu
	int m_spawnDelay;
	// �G�������ɍĐ�����T�E���h�^�C�v
	SoundType m_currentSoundType;
	SoundType m_currentRingoSoundType;
	// �G�L�����摜�n���h��
	int m_hRaraImg;
	// �e�̉摜�n���h��
	int m_hCurrentImg; 
	int m_hChinoImg;
	int m_hMyuImg;
	int m_hNinaImg;
	int m_hVitteImg;
	int m_hCurrentRingoImg;
	int m_hRingoImg;
	int m_hBigringoImg;
	// �e��������
	bool m_isCanShot;
};

