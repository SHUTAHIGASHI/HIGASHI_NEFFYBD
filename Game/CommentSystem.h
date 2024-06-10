#pragma once
#include <vector>
#include <string>
#include "Game.h"

class CommentSystem
{
public:
	CommentSystem();
	virtual ~CommentSystem();

	void InitCommentAndPos();
	void CreateCommentAndPos();
	void CreateDeadCommentAndPos();

	void Init();
	void Update();
	void Draw();

	// �Q�[���I�[�o�[���̏���
	void OnGameOver();
	// �폜�����Ԃ�
	bool IsDelete() { return m_isDelete; }
private:
	// �R�����g�������_���Ŏ擾
	std::string GetRandComment();
	std::string GetRandDeadComment();
	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (CommentSystem::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalCommentUpdate();
	// �R�����g�f�[�^�Ǎ�
	void LoadCommentData();
private:
	// �폜����
	bool m_isDelete;
	// �R�����g�̕\�������
	int m_commentNum;
	// �\������R�����g�ƍ��W
	std::vector<std::string> m_Comments;
	std::vector<std::string> m_DeadComments;
	std::vector<std::string*> m_CurrentComment;
	std::vector<VECTOR*> m_CommentPos;
};

