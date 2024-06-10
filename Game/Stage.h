#pragma once
#include <memory>
#include <vector>

class SceneMain;
class Player;
class EnemyManager;
class MelonCreamSoda;

class Stage
{
public:
	Stage();
	virtual ~Stage();

	void SetMain(SceneMain* main) { m_Main = main; }
	void SetPlayer(Player* player) { m_Player = player; }

	void Init();
	void Update();
	void Draw();

	void OnRestart();
	void OnTimeUp();

private:
	SceneMain* m_Main;
	Player* m_Player;
	// �A�C�e���|�C���^
	MelonCreamSoda* m_Item;
	// �A�C�e���摜�n���h��
	int m_hMelonCreamSodaImg;
};

