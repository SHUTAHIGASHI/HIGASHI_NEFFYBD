#pragma once
#include "Scene.h"
#include <memory>

class Player;
class Stage;
class EnemyManager;
class CommentSystem;

enum class GameMode;

class SceneMain :
    public Scene
{
public:
    // �R���X�g���N�^
    SceneMain(SceneManager& manager);
    // �f�X�g���N�^
    virtual ~SceneMain();

    // �V�[��������
    void Init();
    // �X�V����
    void Update(const InputState& input);
    // �`�揈��
    void Draw();
    // �X�R�A����
    void OnScoreUp();
    // ��_���[�W����
    void OnDamage();
    // �Q�[���I�[�o�[���̏���
    void OnGameOver();
    // �Q�[���N���A���̏���
    void OnGameClear();
    // �ăX�^�[�g���̏���
    void OnRestart();
private:
    // �Q�[���^�C����0�ɂȂ������̏���
    void OnTimeUp();
    // �e�L�X�g�J���[�Ǘ�
    void ChangeTextColor();
    // �c�@�`��
    void DrawPlayerLife();
    // �^�C�����\��
    void DrawGameInfo();
    // ���[�h���ƂɍX�V�����؂�ւ�
    void ChangeUpdateMode();

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void SceneStartUpdate(const InputState& input);
    void NormalModeUpdate(const InputState& input);
    void EndlessModeUpdate(const InputState& input);
    void GameOverUpdate(const InputState& input);
    void GameClearUpdate(const InputState& input);

    // �����o�֐��|�C���^(�X�V)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();
    void QuakeDraw();
private:
    std::shared_ptr<Stage> m_pStage;     // �X�e�[�W
    std::shared_ptr<Player> m_pPlayer;   // �v���C���[
    std::shared_ptr<EnemyManager> m_pEnemy;   // �v���C���[
    std::shared_ptr<CommentSystem> m_pComment;   // �R�����g�V�X�e��
private:
    // ��Փx�I�𔻒�
    bool m_isModeSelected;
    // ���݂̃Q�[�����[�h
    GameMode m_currentGameMode;
    // ���t���[���J�E���g
    int m_countFrame;
    // ���X�^�[�g�܂ł̎���
    int m_delayTime;
    // �w�i�n���h��
    int m_hNeffyImg;
    int m_hBgImg;
    // ��ʗh��X�N���[��
    int m_hQuakeScreen;
    // ��ʗh��̑傫��
    int m_quakeScale;
    // �Q�[������
    int m_gameTime;
    // �Q�[���X�R�A
    int m_gameScore;
    // �J�E���g�_�E���e�L�X�g�J���[
    int m_countTextColor;
};

