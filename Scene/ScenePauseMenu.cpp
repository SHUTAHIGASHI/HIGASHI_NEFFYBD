#include "ScenePauseMenu.h"
#include "Game.h"
#include "SceneManager.h"
#include "SceneOption.h"
#include "SceneTitleMenu.h"

namespace
{
	// 選択可能項目の数
	constexpr int kSelectItemNum = 2;
	// テキスト
	const char* const kTextPause = "～ポーズメニュー～";
	const char* const kTextReturn = "戻る";
	const char* const kTextEndless = "設定";
	const char* const kTextGameEnd = "タイトルへ";
}

ScenePauseMenu::ScenePauseMenu(SceneManager& manager) :
	Scene(manager),
	m_selectedPos(0),
	m_selectedItemName()
{
}

ScenePauseMenu::~ScenePauseMenu()
{

}

void ScenePauseMenu::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		SoundManager::GetInstance().RestartCurrentBGM();
		m_Manager.PopScene();
		return;
	}

	if (input.IsTriggered(InputType::enter))
	{
		SoundManager::GetInstance().PlaySE(SoundType::select);

		if (m_selectedPos == 0)
		{
			SoundManager::GetInstance().RestartCurrentBGM();
			m_Manager.PopScene();
		}
		else if (m_selectedPos == 1)
		{
			m_Manager.PushScene(new SceneOption(m_Manager));
		}
		else if (m_selectedPos == 2)
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
		return;
	}

	if (input.IsTriggered(InputType::up))
	{
		m_selectedPos--;
		if (m_selectedPos < 0) m_selectedPos = kSelectItemNum;
	}
	else if (input.IsTriggered(InputType::down))
	{
		m_selectedPos++;
		if (m_selectedPos > kSelectItemNum) m_selectedPos = 0;
	}
}

void ScenePauseMenu::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawMenuText();
}

std::string ScenePauseMenu::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextReturn;
	}
	else if (textNum == 1)
	{
		text = kTextEndless;
	}
	else if (textNum == 2)
	{
		text = kTextGameEnd;
	}

	return text;
}

void ScenePauseMenu::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextPause) / 2));
	drawY = Game::kScreenHeightHalf - 100.0f;
	DrawStringF(drawX, drawY, kTextPause, 0xffffff);

	for (int i = 0; i <= kSelectItemNum; i++)
	{
		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		drawY = static_cast<float>(Game::kScreenHeightHalf) + (i * 40);

		DrawFormatStringF(drawX, drawY, 0xffffff, "%s", tSelectedItemName.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(Game::kScreenHeightHalf) + (m_selectedPos * 40);
	DrawFormatStringF(drawX, drawY, Game::kColorRed, "%s", m_selectedItemName.c_str());
}
