#pragma once
#include "Game.h"
#include "EffectType.h"

// エフェクトベース
class EffectBase
{
public:
	EffectBase(EffectType type, int handle);
	virtual ~EffectBase();

	// 更新処理
	virtual void Update() = 0;
	// エフェクト停止
	void StopCurrentEffect();
	// エフェクト作成
	void CreateEffect();

	// エフェクトの各種設定
	void SetPosition(VECTOR pos);
	void SetPositionOnlyZ(float posZ);
	void SetEffectPlayingSpeed(float speed);
	void SetEffectColor(int r, int g, int b, int a);

	// エフェクトタイプ取得
	EffectType GetEffectType() { return m_type; }
	// 削除判定取得
	bool IsDelete() { return m_isDelete; }
protected:

protected:
	// エフェクトを削除するかどうか
	bool m_isDelete;

	// エフェクトタイプ
	EffectType m_type;

	// エフェクトのハンドル
	int m_hEffectResource;
	int m_currentPlayingEffect;

	// 描画座標
	VECTOR m_pos;
};

