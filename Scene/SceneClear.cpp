#include "SceneClear.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneMain.h"

namespace
{
	// 選択可能項目の数
	constexpr int kSelectItemNum = 1;
	// テキスト
	const char* const kTextTitle = "タイトルへ戻る";
	// スクロール速度
	constexpr float kScrollSpeed = 6.0f;
}

SceneClear::SceneClear(SceneManager& manager) :
	Scene(manager),
	m_countFrame(0),
	m_isScrollEnd(false)
{
	m_hBgImg = LoadGraph("Data/ImageData/GameBg.jpg");
	m_hClearImg = LoadGraph("Data/ImageData/GameClearImg.png");
	// グラフサイズ取得
	GetGraphSize(m_hClearImg, &m_ClearGraphX, &m_ClearGraphY);
	m_bgPos = VGet(Game::kScreenWidthHalf, 0.0f, 0.0f);
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_hClearImg);
}

void SceneClear::Update(const InputState& input)
{
	m_countFrame++;
	if (m_countFrame > 10000)
	{
		m_countFrame = 0;
	}

	if (input.IsPressed(InputType::up))
	{
		m_bgPos.y += kScrollSpeed;
		if (m_bgPos.y > 0.0f)
		{
			m_bgPos.y = 0.0f;
		}
	}
	else if (input.IsPressed(InputType::down))
	{
		m_bgPos.y += -kScrollSpeed;
		if (m_bgPos.y < -Game::kScreenHeight * 3)
		{
			m_bgPos.y = -Game::kScreenHeight * 3;
		}
	}

	if (m_bgPos.y <= -Game::kScreenHeight * 3)
	{
		m_isScrollEnd = true;
	}
	else
	{
		m_isScrollEnd = false;
	}

	if (m_isScrollEnd)
	{
		if (input.IsTriggered(InputType::enter))
		{
			SoundManager::GetInstance().PlaySE(SoundType::select);

			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
			return;
		}
	}
}

void SceneClear::Draw()
{
	DrawExtendGraphF(0.0f, 0.0f, Game::kScreenWidth, Game::kScreenHeight, m_hBgImg, true);
	DrawRotaGraphF(m_bgPos.x, m_bgPos.y + m_ClearGraphY / 2, 1.0, 0.0, m_hClearImg, true);
	if (m_isScrollEnd)
	{
		DrawMenuText();
	}
	else
	{
		if ((m_countFrame / 10) % 6 != 0)
		{
			DrawFormatStringF(Game::kScreenWidth - 200.0f, 
				Game::kScreenHeight - 55, Game::kColorRed, "下へつづく↓");
		}
	}
}

void SceneClear::DrawMenuText()
{
	float stringLength = static_cast<float>(GetDrawFormatStringWidth(kTextTitle));
	if ((m_countFrame / 10) % 6 != 0)
	{
		DrawFormatStringF(Game::kScreenWidthHalf - (stringLength / 2), Game::kScreenHeight - 55, Game::kColorRed, "%s", kTextTitle);
	}
}
