#include "CommentSystem.h"

namespace
{
	// �R�����g�̗���鑬�x
	constexpr float kCommentSpeed = 6.0f;
	// �R�����g�̗�
	constexpr int kCommentNumMin = 4;
	constexpr int kCommentNumMax = 13;
}

CommentSystem::CommentSystem():
	m_updateFunc(&CommentSystem::NormalCommentUpdate),
	m_isDelete(false),
	m_commentNum(kCommentNumMin),
	m_CurrentComment(),
	m_CommentPos()
{
	LoadCommentData();
}

CommentSystem::~CommentSystem()
{
}

void CommentSystem::InitCommentAndPos()
{
	m_CurrentComment.push_back(new std::string(GetRandComment()));
	m_CommentPos.push_back(new VECTOR());
	float posX = static_cast<float>(GetRand(static_cast<int>(Game::kScreenWidth)));
	float posY = static_cast<float>(GetRand(static_cast<int>(Game::kScreenHeight - (Game::kFontSize * 2))) + Game::kFontSize);
	m_CommentPos.back()->x = Game::kScreenWidth + posX;
	m_CommentPos.back()->y = posY;
}

void CommentSystem::CreateCommentAndPos()
{
	m_CurrentComment.push_back(new std::string(GetRandComment()));
	m_CommentPos.push_back(new VECTOR());
	float posY = static_cast<float>(GetRand(static_cast<int>(Game::kScreenHeight - (Game::kFontSize * 2))) + Game::kFontSize);
	m_CommentPos.back()->x = Game::kScreenWidth;
	m_CommentPos.back()->y = posY;
}

void CommentSystem::CreateDeadCommentAndPos()
{
	m_CurrentComment.push_back(new std::string(GetRandDeadComment()));
	m_CommentPos.push_back(new VECTOR());
	float posX = static_cast<float>(GetRand(static_cast<int>(Game::kScreenWidth)));
	float posY = static_cast<float>(GetRand(static_cast<int>(Game::kScreenHeight - (Game::kFontSize * 2))) + Game::kFontSize);
	m_CommentPos.back()->x = Game::kScreenWidth + posX;
	m_CommentPos.back()->y = posY;
}

void CommentSystem::Init()
{
	while (m_CurrentComment.size() < kCommentNumMin)
	{
		InitCommentAndPos();
	}
}

void CommentSystem::Update()
{
	//�X�V�����̃����o�֐��|�C���^
	(this->*m_updateFunc)();

	int countCom = 0;
	for (int i = 0; i < m_CurrentComment.size(); i++)
	{
		m_CommentPos[i]->x -= kCommentSpeed;

		int textLength = GetDrawFormatStringWidth(m_CurrentComment[i]->c_str());
		if (m_CommentPos[i]->x + textLength < 0.0f)
		{
			m_CurrentComment.erase(m_CurrentComment.begin() + i);
			m_CommentPos.erase(m_CommentPos.begin() + i);
			countCom++;
		}
	}

	if (countCom >= m_CurrentComment.size())
	{
		m_isDelete = true;
	}
}

void CommentSystem::Draw()
{
	for (int i = 0; i < m_CurrentComment.size(); i++)
	{
		DrawFormatStringF(m_CommentPos[i]->x, m_CommentPos[i]->y, 0xffffff, m_CurrentComment[i]->c_str());
	}
}

void CommentSystem::OnGameOver()
{
	while (m_CurrentComment.size() < kCommentNumMax)
	{
		CreateDeadCommentAndPos();
	}
}

std::string CommentSystem::GetRandComment()
{
	int n = GetRand(static_cast<int>(m_Comments.size() - 1));
	std::string resultComment = m_Comments[n];
	for (int i = 0; i < m_CurrentComment.size(); i++)
	{
		if (m_CurrentComment[i]->c_str() == resultComment)
		{
			i = -1;
			n = GetRand(static_cast<int>(m_Comments.size() - 1));
			resultComment = m_Comments[n];
		}
	}

	return resultComment;
}

std::string CommentSystem::GetRandDeadComment()
{
	int n = GetRand(static_cast<int>(m_DeadComments.size() - 1));
	std::string resultComment = m_DeadComments[n];
	for (int i = 0; i < m_CurrentComment.size(); i++)
	{
		if (m_CurrentComment[i]->c_str() == resultComment)
		{
			i = -1;
			n = GetRand(static_cast<int>(m_DeadComments.size() - 1));
			resultComment = m_DeadComments[n];
		}
	}

	return resultComment;
}

void CommentSystem::NormalCommentUpdate()
{
	while (m_CurrentComment.size() < kCommentNumMin)
	{
		CreateCommentAndPos();
	}
}

void CommentSystem::LoadCommentData()
{
	m_Comments = {
	"N(�G�k)@���@���f���[�F�����̨" ,
	"����҂����F�����̨" ,
	"����҂����F���w" ,
	"�����F��񂲁[�I" ,
	"���C�g�J���X�F�ɂ��͂��[�I",
	"�����K�F�ɂ��͂��[�I",
	"�Ƃ�F���܂��I",
	"�M���M�[�F�������Ə΂����Ⴄw",
	"�M���M�[�F���[���I���[���I���[���I",
	"�Ђ炪�Ȃ̂�Ԃ�F��񂲂ł����H",
	"�Ђ炪�Ȃ̂�Ԃ�F��񂲉������Ă�́Hw",
	"Anekumene�i���˂��߁[�ˁj�F�̨�ׂĂ��Ă�",
	"�肴�ҁF�l�t�B���񂪂�΂�[�I�I",
	"Satellit FELT�F������I",
	"yadonne(��ǂ��)�F���킢���[�I",
	"�^�N�e�B���F�l�t�B���񂱂����݂ā[�I",
	"�g(�G��)�уA�I�F�������񂶁I�I",
	"�肴�ҁF�v�w���܂��Ă��Ƃ�",
	"���������k�F�����l�ɕ�����ȁIw" ,
	"yadonne(��ǂ��)�F����VALIS�I�I",
	"����҂����F��������Q�[�����܂���",
	"�����F�Ȃ�ł��Ƃ��I�H",
	"N(�G�k)@���@���f���[�F�����z�ѓX�͂�񂲂�����"
	};

	m_DeadComments = {
	"����҂����F���������I�H",
	"�����F�������I" ,
	"�肴�ҁF��������I",
	"�Ђ炪�Ȃ̂�Ԃ�F�ӂށB",
	"���������k�F����VALIS�I" ,
	"N(�G�k)@���@���f���[�F33-4",
	"�Ƃ�F���ŃN���A���������I",
	"�g(�G��)�уA�I�F�S�{��",
	"�����K�F�l�t�B����Ȃ���v�I",
	"�M���M�[�F��ݷް�����Ƃ��̨�ݎ������I",
	"�߃m�g�k�F���s���Ă݂悤�I",
	"�G���y���[(��)�F�����邢����I",
	"�A�j@���@���f���[�Fwwwww",
	"�A�j@���@���f���[�F������Ȃ�����w",
	"�G���y���[(��)�F��񂲂̈З͂�΂�w"
	};
}
