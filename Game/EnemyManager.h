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
	// レベルアップ
	void OnLevelUp();
	// 再スタートの処理
	void OnRestart();
private:
	// 弾ランダム生成
	void SetRandObject();
	// 敵生成処理
	void OnSpawnEnemy();
	// 不要な敵を削除する
	void DeleteDisableEnemy();

private:
	Player* m_Player;
	SceneMain* m_pMain;
	// 敵配列
	std::vector<std::shared_ptr<EnemyBase>> m_pEnemies;
	EnemySpawner* m_Rara;
	// 敵の生成間隔
	int m_spawnDelay;
	// 敵生成時に再生するサウンドタイプ
	SoundType m_currentSoundType;
	SoundType m_currentRingoSoundType;
	// 敵キャラ画像ハンドル
	int m_hRaraImg;
	// 弾の画像ハンドル
	int m_hCurrentImg; 
	int m_hChinoImg;
	int m_hMyuImg;
	int m_hNinaImg;
	int m_hVitteImg;
	int m_hCurrentRingoImg;
	int m_hRingoImg;
	int m_hBigringoImg;
	// 弾生成判定
	bool m_isCanShot;
};

