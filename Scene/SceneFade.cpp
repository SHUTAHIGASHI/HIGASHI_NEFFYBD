#include "SceneFade.h"
#include "SceneManager.h"

SceneFade::SceneFade(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneFade::CloseUpdate),
	m_isFadeClose(false),
	m_isFadeOpen(false),
	m_fadeNum(0)
{

}

SceneFade::~SceneFade()
{
}

void SceneFade::Update(const InputState& input)
{
	(this->*m_updateFunc)();
}

void SceneFade::Draw()
{
	// フェード処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeNum);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneFade::CloseUpdate()
{
	m_fadeNum += 10;

	if (m_fadeNum > 255)
	{
		m_fadeNum = 255;
		m_isFadeClose = true;
		m_updateFunc = &SceneFade::OpenUpdate;
	}
}

void SceneFade::OpenUpdate()
{
	m_fadeNum -= 10;

	if (m_fadeNum < 0)
	{
		m_fadeNum = 0;
		m_isFadeOpen = true;
	}
}
