#include "TempEffectBase.h"

void TempEffectBase::Update()
{
	SetPosPlayingEffekseer3DEffect(m_currentPlayingEffect, m_pos.x, m_pos.y, m_pos.z);

	//todo ���S���̃G�t�F�N�g����SetPos�Ńo�O���ΏC������
	if (IsEffekseer3DEffectPlaying(m_currentPlayingEffect) != 0)
	{
		m_isDelete = true;
	}
}
