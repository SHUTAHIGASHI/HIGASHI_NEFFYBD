#include "EffectBase.h"

EffectBase::EffectBase(EffectType type, int handle) :
	m_isDelete(false),
	m_type(type),
	m_hEffectResource(handle),
	m_currentPlayingEffect(-1),
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
}

EffectBase::~EffectBase()
{
}

void EffectBase::SetPosition(VECTOR pos)
{
	m_pos = pos;
}

void EffectBase::SetPositionOnlyZ(float posZ)
{
	m_pos.z = posZ;
}

void EffectBase::SetEffectPlayingSpeed(float speed)
{
	SetSpeedPlayingEffekseer3DEffect(m_currentPlayingEffect, speed);
}

void EffectBase::SetEffectColor(int r, int g, int b, int a)
{
	SetColorPlayingEffekseer3DEffect(m_currentPlayingEffect, r, g, b, a);
}

void EffectBase::StopCurrentEffect()
{
	bool result = StopEffekseer3DEffect(m_currentPlayingEffect);
	assert(result == 0);
}

void EffectBase::CreateEffect()
{
	m_currentPlayingEffect = PlayEffekseer3DEffect(m_hEffectResource);
	assert(m_hEffectResource != -1);
}

