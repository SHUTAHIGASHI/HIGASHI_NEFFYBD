#include "SceneModeSelect.h"
#include "SceneManager.h"
#include "Game.h"

namespace
{
	// 項目数
	constexpr int kSelectItemNum = 1;
	// テキスト
	const char* const kTextSceneName = "モード選択";
	const char* const kTextNormal = "ノーマル";
	const char* const kTextEndless = "エンドレス";
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 30.0f;
}

SceneModeSelect::SceneModeSelect(SceneManager& manager):
	Scene(manager),
	m_countFrame(0),
	m_gameMode(),
	m_selectedItemName(),
	m_selectedPos(0),
	m_hBoardImg(-1)
{
	m_hBoardImg = LoadGraph("Data/ImageData/board.png");
}

SceneModeSelect::~SceneModeSelect()
{
	DeleteGraph(m_hBoardImg);
}

void SceneModeSelect::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
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

	if (input.IsTriggered(InputType::enter))
	{
		if (m_selectedPos == 0)
		{
			GameDataManager::GetInstance().SetGameMode(GameMode::normal);
		}
		else if (m_selectedPos == 1)
		{
			GameDataManager::GetInstance().SetGameMode(GameMode::endless);
		}

		SoundManager::GetInstance().PlaySE(SoundType::select);
		m_Manager.PopScene();

		return;
	}
}

void SceneModeSelect::Draw()
{
	// 背景画像
	DrawRotaGraph(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0f, 0.0f, m_hBoardImg, true);

	DrawMenuText();
}

std::string SceneModeSelect::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextNormal;
	}
	else if (textNum == 1)
	{
		text = kTextEndless;
	}

	return text;
}

void SceneModeSelect::DrawMenuText()
{
	int drawX = 0, drawY = 0;
	drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextSceneName) / 2));
	drawY = static_cast<int>(Game::kScreenHeightHalf - 120.0f);
	DrawString(drawX, drawY, kTextSceneName, 0xffffff);

	drawX = 0, drawY = static_cast<int>(Game::kScreenHeightHalf);
	std::string tText;
	for (int i = 0; i <= kSelectItemNum; i++)
	{
		tText = GetCurrentText(i);
		drawX = static_cast<int>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tText.c_str()) / 2));
		drawY = static_cast<int>(kTextDrawPosY + (i * 60));
		DrawFormatString(drawX, drawY, 0xffffff, "%s", tText.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	int textLength = GetDrawFormatStringWidth(m_selectedItemName.c_str());
	drawX = static_cast<int>(Game::kScreenWidthHalf - (textLength / 2));
	drawY = static_cast<int>(kTextDrawPosY + (m_selectedPos * 60));

	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatString(drawX, drawY, Game::kColorRed, "%s", m_selectedItemName.c_str());
	}
}
