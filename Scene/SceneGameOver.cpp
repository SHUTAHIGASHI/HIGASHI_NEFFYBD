#include "SceneGameOver.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"

namespace
{
	// 選択肢の数
	constexpr int kSelectItemNum = 1;
	// 描画するテキスト
	const char* const kTextGameClear = "ラ王様の怒りを鎮められなかった。。。";
	const char* const kTextRestart = "リスタート";
	const char* const kTextTitle = "タイトルへ";

	// 座標関係
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf + 150.0f;
	constexpr float kTextDistance = 60.0f;
}

SceneGameOver::SceneGameOver(SceneManager& manager):
	Scene(manager),
	m_updateFunc(&SceneGameOver::SceneStartUpdate),
	m_fadeNum(0),
	m_isFadeEnd(false),
	m_windowDrawPosX(0),
	m_windowDrawPosY(0),
	m_selectedPos(0),
	m_selectedItemName("EMPTY")
{
	m_windowDrawPosX = Game::kScreenWidthHalf;
	m_windowDrawPosY = Game::kScreenHeightHalf;

	SoundManager::GetInstance().PlaySE(SoundType::yabai);
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Update(const InputState& input)
{
	//更新処理のメンバ関数ポインタ
	(this->*m_updateFunc)(input);
}

void SceneGameOver::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeNum);
	DrawBox(0, 0, static_cast<int>(Game::kScreenWidth), static_cast<int>(Game::kScreenHeight), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_isFadeEnd)
	{
		SetFontSize(40);
		DrawFormatStringF(Game::kScreenWidthHalf - 195, Game::kScreenHeightHalf, 0xffffff, "避けたりんご %3d 個", GameDataManager::GetInstance().GetGameScore());
		SetFontSize(Game::kFontSize);

		DrawMenuText();
	}
}

void SceneGameOver::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextGameClear) / 2));
	drawY = Game::kScreenHeightHalf - 160.0f;
	DrawStringF(drawX, drawY, kTextGameClear, 0xffffff);

	for (int i = 0; i <= kSelectItemNum; i++)
	{
		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);
		DrawFormatStringF(drawX, drawY, 0xffffff, "%s", tSelectedItemName.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	DrawFormatStringF(drawX, drawY, Game::kColorRed, "%s", m_selectedItemName.c_str());
}

std::string SceneGameOver::GetCurrentText(int n)
{
	std::string text;

	if (n == 0)
	{
		text = kTextRestart;
	}
	else if (n == 1)
	{
		text = kTextTitle;
	}

	return text;
}

void SceneGameOver::NormalUpdate(const InputState& input)
{
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
		SoundManager::GetInstance().PlaySE(SoundType::select);
		if (m_selectedPos == 0)
		{
			m_Manager.PopScene();
		}
		else
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
	}
}

void SceneGameOver::SceneStartUpdate(const InputState& input)
{
	m_fadeNum += 5;
	if (m_fadeNum > 230)
	{
		m_fadeNum = 230;
		m_isFadeEnd = true;
		m_updateFunc = &SceneGameOver::NormalUpdate;
	}
}
