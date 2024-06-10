#include "TempEffectBase.h"

void TempEffectBase::Update()
{
	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, m_pos.x, m_pos.y, m_pos.z);

	//todo 死亡時のエフェクトだけSetPosでバグる絶対修正しろ
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect) != 0)
	{
		m_isDelete = true;
	}
}
