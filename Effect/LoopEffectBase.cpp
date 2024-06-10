#include "LoopEffectBase.h"

void LoopEffectBase::Update()
{
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect) != 0)
	{
		m_currentPlayingEffect = PlayEffekseer3DEffect(m_hEffectResource);
	}

	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, m_pos.x, m_pos.y, m_pos.z);
	assert(m_hEffectResource != -1);
}
