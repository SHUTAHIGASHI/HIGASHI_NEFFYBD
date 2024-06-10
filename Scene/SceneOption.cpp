#include "SceneOption.h"
#include "SceneManager.h"
#include "SoundManager.h"

namespace
{
	// オプション画面描画座標
	constexpr int kMenuWidth = 200;
	constexpr int kMenuHeight = 200;
	// テキスト描画位置
	constexpr float kTextDrawPosY = Game::kScreenHeightHalf - 80.0f;
	// テキスト描画間隔
	constexpr float kTextDistance = 60.0f;

	// 音量変化量
	constexpr int kVolumeChangeNum = 10;

	// 選択可能項目の数
	constexpr int kSelectItemNum = 3;
	// テキスト
	const char* const kTextScene = "～設定～";
	const char* const kTextReturn = "戻る";
	const char* const kTextBGM = "音楽";
	const char* const kTextSE = "効果音";
	const char* const kTextSave = "保存して閉じる";
}

SceneOption::SceneOption(SceneManager& manager) :
	Scene(manager),
	m_volumeBGM(0),
	m_volumeSE(0),
	m_selectedPos(0),
	m_selectedItemName()
{
	Init();
}

SceneOption::~SceneOption()
{
}

void SceneOption::Init()
{
	m_volumeSE =  SoundManager::GetInstance().GetSEVolume();
	m_volumeBGM = SoundManager::GetInstance().GetBGMVolume();
}

void SceneOption::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PopScene();
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

	if (m_selectedPos == 0)
	{
		if (input.IsTriggered(InputType::enter))
		{
			SoundManager::GetInstance().PlaySE(SoundType::select);
			m_Manager.PopScene();
		}
	}
	else if (m_selectedPos == 1)
	{
		ChangeVolume(input, m_volumeBGM);
	}
	else if (m_selectedPos == 2)
	{
		ChangeVolume(input, m_volumeSE);
	}
	else if (m_selectedPos == 3)
	{
		if (input.IsTriggered(InputType::enter))
		{
			SetVolumeInfo();
			SoundManager::GetInstance().PlaySE(SoundType::select);
			m_Manager.PopScene();
		}
	}
}

void SceneOption::Draw()
{
	int drawX = Game::kScreenWidthHalf - kMenuWidth, drawY = Game::kScreenHeightHalf - kMenuHeight;
	int drawX2 = Game::kScreenWidthHalf + kMenuWidth, drawY2 = Game::kScreenHeightHalf + kMenuHeight;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 225);
	DrawBox(drawX, drawY, drawX2, drawY2, 0x000000, true);
	DrawBox(drawX, drawY, drawX2, drawY2, 0xffffff, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawMenuText();
	DrawSoundBar();
}

void SceneOption::ChangeVolume(const InputState& input, int &vol)
{
	if (input.IsTriggered(InputType::right))
	{
		vol+= kVolumeChangeNum;
		if (vol > 100) vol = 100;
	}
	if (input.IsTriggered(InputType::left))
	{
		vol-= kVolumeChangeNum;
		if (vol < 0) vol = 0;
	}
}

void SceneOption::SetVolumeInfo()
{
	SoundManager::GetInstance().SetSEVolume(m_volumeSE);
	SoundManager::GetInstance().SetBGMVolume(m_volumeBGM);
}

void SceneOption::DrawSoundBar()
{
	int barColorBGM = 0xffffff, barColorSE = 0xffffff;
	if (m_selectedPos == 1) barColorBGM = Game::kColorRed;
	if (m_selectedPos == 2) barColorSE = Game::kColorRed;

	int drawX, drawX2;
	int drawY, drawY2;

	int n = 0;
	n = m_volumeBGM / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		drawX = Game::kScreenWidthHalf + (i * 15), drawX2 = drawX + 10;
		drawY = 342, drawY2 = drawY + 30;

		DrawBox(drawX, drawY, drawX2, drawY2, barColorBGM, true);
	}

	n = m_volumeSE / kVolumeChangeNum;
	for (int i = 0; i < n; i++)
	{
		drawX = Game::kScreenWidthHalf + (i * 15), drawX2 = drawX + 10;
		drawY = 402, drawY2 = drawY + 30;

		DrawBox(drawX, drawY, drawX2, drawY2, barColorSE, true);
	}
}

void SceneOption::DrawMenuText()
{
	float drawX = 0.0f, drawY = 0.0f;
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(kTextScene) / 2));
	drawY = Game::kScreenHeightHalf - 160.0f;
	DrawStringF(drawX, drawY, kTextScene, 0xffffff);

	for (int i = 0; i <= kSelectItemNum; i++)
	{
		std::string tSelectedItemName;
		tSelectedItemName = GetCurrentText(i);
		drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		drawY = static_cast<float>(kTextDrawPosY) + (i * kTextDistance);

		if (i == 1 || i == 2)
		{
			drawX = static_cast<float>((Game::kScreenWidthHalf - 100)-(GetDrawFormatStringWidth(tSelectedItemName.c_str()) / 2));
		}

		DrawFormatStringF(drawX, drawY, 0xffffff, "%s", tSelectedItemName.c_str());
	}

	m_selectedItemName = GetCurrentText(m_selectedPos);
	drawX = static_cast<float>(Game::kScreenWidthHalf - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	drawY = static_cast<float>(kTextDrawPosY) + (m_selectedPos * kTextDistance);
	if (m_selectedPos == 1 || m_selectedPos == 2)
	{
		drawX = static_cast<float>((Game::kScreenWidthHalf - 100) - (GetDrawFormatStringWidth(m_selectedItemName.c_str()) / 2));
	}
	DrawFormatStringF(drawX, drawY, Game::kColorRed, "%s", m_selectedItemName.c_str());
}

std::string SceneOption::GetCurrentText(int textNum)
{
	std::string text;

	if (textNum == 0)
	{
		text = kTextReturn;
	}
	else if (textNum == 1)
	{
		text = kTextBGM;
	}
	else if (textNum == 2)
	{
		text = kTextSE;
	}
	else if (textNum == 3)
	{
		text = kTextSave;
	}

	return text;
}