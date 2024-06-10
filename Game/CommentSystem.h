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

	// ゲームオーバー時の処理
	void OnGameOver();
	// 削除判定を返す
	bool IsDelete() { return m_isDelete; }
private:
	// コメントをランダムで取得
	std::string GetRandComment();
	std::string GetRandDeadComment();
	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (CommentSystem::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalCommentUpdate();
	// コメントデータ読込
	void LoadCommentData();
private:
	// 削除判定
	bool m_isDelete;
	// コメントの表示する量
	int m_commentNum;
	// 表示するコメントと座標
	std::vector<std::string> m_Comments;
	std::vector<std::string> m_DeadComments;
	std::vector<std::string*> m_CurrentComment;
	std::vector<VECTOR*> m_CommentPos;
};

