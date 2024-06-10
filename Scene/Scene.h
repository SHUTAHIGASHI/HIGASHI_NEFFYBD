#pragma once

// #include�ł͂Ȃ��v���g�^�C�v�錾���g�p����
class SceneManager; // �V�[���}�l�[�W���[
class InputState;	// ���̓X�e�[�g
// ���̎��_�ł�SceneManager��InputState��
// �|�C���^�������͎Q�ƂƂ��Ă��������Ȃ�

/// <summary>
/// �V�[�����N���X
/// </summary>

class Scene
{
public:
	Scene(SceneManager& manager) : m_Manager(manager) {}
	virtual ~Scene() {};

	// �V�[�����X�V����
	virtual void Update(const InputState& input) = 0;
	// �V�[����`�悷��
	virtual void Draw() = 0;
protected:
	SceneManager& m_Manager; // �V�[���}�l�[�W���[�ւ̎Q��
};
