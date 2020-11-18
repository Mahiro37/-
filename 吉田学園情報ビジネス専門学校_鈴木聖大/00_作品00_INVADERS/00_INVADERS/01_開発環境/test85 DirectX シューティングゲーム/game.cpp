//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "title.h"
#include "game.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;

//=====================================================
//����������
//=====================================================
void InitGame(void)
{
	//bg�̏���������
	InitBg();

	// �v���C���[�̏���������
	InitPlayer();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�G�̏���������
	InitEnemy();

	SetEnemy(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 3);
	SetEnemy(D3DXVECTOR3(600.0f, 200.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 5);
	SetEnemy(D3DXVECTOR3(900.0f, 100.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 0, 3);
}

//=====================================================
//�I������
//=====================================================
void UninitGame(void)
{
	//bg�̏I������
	UninitBg();

	// �v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();
}

//=====================================================
//�X�V����
//=====================================================
void UpdateGame(void)
{
	UpdateBg();

	UpdateBullet();

	UpdateEnemy();

	UpdateExplosion();

	UpdatePlayer();
}

//=====================================================
//�`�揈��
//=====================================================
void DrawGame(void)
{
	// bg�̕`�揈��
	DrawBg();

	//�G�̕`�揈��
	DrawEnemy();

	// �|���S���̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();
}

//=====================================================
//�ݒ菈��
//=====================================================
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}

//=====================================================
//�f�o�C�X�̎擾
//=====================================================
GAMESTATE GetGamesate(void)
{
	return g_gamestate;
}