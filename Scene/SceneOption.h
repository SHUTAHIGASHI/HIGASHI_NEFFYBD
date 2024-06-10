#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>

enum class volume
{
    SE,
    BGM
};

class SceneOption :
    public Scene
{
public:
    SceneOption(SceneManager& manager);
    virtual ~SceneOption();

    // 初期化
    void Init();
    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();

private: // プライベート関数
    // 音量の設定
    void ChangeVolume(const InputState& input, int& vol);
    // 変更した音量情報を反映させる
    void SetVolumeInfo();
    // テキスト描画位置
    void DrawSoundBar();
    // テキスト情報の描画
    void DrawMenuText();
    // 選択中の文字列を返す
    std::string GetCurrentText(int textNum);
private:
    // 音量
    int m_volumeBGM;
    int m_volumeSE;
    // 選択位置
    int m_selectedPos;
    std::string m_selectedItemName;
};
