#pragma once
#include "Scene.h"
#include <string>
#include "Game.h"

class SceneGameOver :
	public Scene
{
public:
	SceneGameOver(SceneManager& manager);
	virtual ~SceneGameOver();

	void Update(const InputState& input);
	void Draw();

private:
	// テキスト描画
	void DrawMenuText();
	// 指定したテキストを返す
	std::string GetCurrentText(int n);

	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (SceneGameOver::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate(const InputState& input);
	void SceneStartUpdate(const InputState& input);

private:
	// フェード数値
	int m_fadeNum;
	// フェード完了判定
	bool m_isFadeEnd;
	// ゲームオーバーウィンドウの描画座標
	float m_windowDrawPosX;
	float m_windowDrawPosY;
	// 選択中の項目
	int m_selectedPos;
	// 選択中の項目名
	std::string m_selectedItemName;
};

