#include "CommentSystem.h"

namespace
{
	// コメントの流れる速度
	constexpr float kCommentSpeed = 6.0f;
	// コメントの量
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
	//更新処理のメンバ関数ポインタ
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
	"N(エヌ)@ヴァンデラー：さすﾈﾌｨ" ,
	"しゅぴちゃん：さすﾈﾌｨ" ,
	"しゅぴちゃん：りんごw" ,
	"レヴ：りんごー！" ,
	"ライトカラス：にゃんはおー！",
	"レンガ：にゃんはおー！",
	"とら：うまい！",
	"ギンギー：声聞くと笑っちゃうw",
	"ギンギー：ラーラ！ラーラ！ラーラ！",
	"ひらがなのりぶら：りんごですか？",
	"ひらがなのりぶら：りんご何個持ってるの？w",
	"Anekumene（あねくめーね）：ﾈﾌｨﾗﾗてぇてぇ",
	"りざぴ：ネフィさんがんばれー！！",
	"Satellit FELT：難しそう！",
	"yadonne(やどんね)：かわいいー！",
	"タクティン：ネフィさんこっちみてー！",
	"紅(雑木)林アオ：いいかんじ！！",
	"りざぴ：夫婦喧嘩ってことか",
	"しく＠生徒：ラ王様に負けるな！w" ,
	"yadonne(やどんね)：がんVALIS！！",
	"しゅぴちゃん：操桃さんゲームうまそう",
	"操桃：なんですとぉ！？",
	"N(エヌ)@ヴァンデラー：瓦利斯飯店はりんごが舞う"
	};

	m_DeadComments = {
	"しゅぴちゃん：ざっきりん！？",
	"レヴ：おしい！" ,
	"りざぴ：次いける！",
	"ひらがなのりぶら：ふむ。",
	"しく＠生徒：がんVALIS！" ,
	"N(エヌ)@ヴァンデラー：33-4",
	"とら：次でクリアいけそう！",
	"紅(雑木)林アオ：鬼畜だ",
	"レンガ：ネフィさんなら大丈夫！",
	"ギンギー：ｷﾞﾝｷﾞｰ死すともﾈﾌｨｻﾝ死せず！",
	"罪ノ使徒：次行ってみよう！",
	"エンペラー(仮)：いけるいける！",
	"アニ@ヴァンデラー：wwwww",
	"アニ@ヴァンデラー：避けれなかったw",
	"エンペラー(仮)：りんごの威力やばいw"
	};
}
