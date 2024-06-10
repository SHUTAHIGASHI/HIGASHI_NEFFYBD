#pragma once
#include "Game.h"
#include "EffectType.h"

// �G�t�F�N�g�x�[�X
class EffectBase
{
public:
	EffectBase(EffectType type, int handle);
	virtual ~EffectBase();

	// �X�V����
	virtual void Update() = 0;
	// �G�t�F�N�g��~
	void StopCurrentEffect();
	// �G�t�F�N�g�쐬
	void CreateEffect();

	// �G�t�F�N�g�̊e��ݒ�
	void SetPosition(VECTOR pos);
	void SetPositionOnlyZ(float posZ);
	void SetEffectPlayingSpeed(float speed);
	void SetEffectColor(int r, int g, int b, int a);

	// �G�t�F�N�g�^�C�v�擾
	EffectType GetEffectType() { return m_type; }
	// �폜����擾
	bool IsDelete() { return m_isDelete; }
protected:

protected:
	// �G�t�F�N�g���폜���邩�ǂ���
	bool m_isDelete;

	// �G�t�F�N�g�^�C�v
	EffectType m_type;

	// �G�t�F�N�g�̃n���h��
	int m_hEffectResource;
	int m_currentPlayingEffect;

	// �`����W
	VECTOR m_pos;
};

