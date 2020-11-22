//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "wallblock.h"
#include "shadow.h"
#include "enemy.h"
#include "damageblock.h"
#include "bullet.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "clearlogo.h"
#include "gameoverlogo.h"
#include "blur.h"
#include "borderlogo.h"
#include "startlogo.h"
#include "effect.h"
#include "barrier.h"
#include "controller.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCntStartState;
int g_nCntFinishState;
float g_Blockx;
bool isCamera;

//=====================================================
//����������
//=====================================================
void InitGame(void)
{
	g_nCntStartState = 0;
	g_nCntFinishState = 0;
	g_Blockx = 0;
	isCamera = false;

	int nCntBlock;

	//�Q�[���X�^�[�g���S�̏�����
	InitStartlogo();

	//�Q�[���N���A���S�̏�����
	InitClearlogo();

	//�Q�[���I�[�o�[���S�̏�����
	InitGameoverlogo();

	//���S�̋��E���̏�����
	InitBorderlogo();

	//�ڂ����̏�����
	InitBlur();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�|���S���̏�����
	InitPolygon();

	//�o���A�̏�����
	InitBarrier();
	SetBarrier(D3DXVECTOR3(0, 2, 10), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 15.0f));

	//���f���̏�����
	InitPlayer();

	//�G�̏�����
	InitEnemy();
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, 110.0f), 0, 0);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, 110.0f), 0, 1);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, 110.0f), 0, 2);
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, 0.0f), 0, 3);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, 0.0f), 0, 4);
	SetEnemy(D3DXVECTOR3(-110.0f, 2.0f, -110.0f), 0, 5);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, -110.0f), 0, 6);
	SetEnemy(D3DXVECTOR3(110.0f, 2.0f, -110.0f), 0, 7);
	SetEnemy(D3DXVECTOR3(0.0f, 2.0f, 10.0f), 1, 8);

	//�J�����̏�����
	InitCamera();

	//���C�g�̏�����
	InitLight();

	////�e�̏�����
	//InitShadow();

	//�e�̏�����
	InitBullet();

	//�_���[�W�u���b�N�̏�����
	InitDamageblock();
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-158 + g_Blockx, 2, 53), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 1)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-158 + g_Blockx, 2, -53), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 2)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(-53, 2, 158 - g_Blockx), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}
		else if (i == 3)
		{
			for (nCntBlock = 0; nCntBlock < 17; nCntBlock++)
			{
				if (nCntBlock == 6 || nCntBlock == 11)
				{
					g_Blockx += 17.5f;
				}
				SetDamageblock(D3DXVECTOR3(52, 2, 158 - g_Blockx), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 0);
				g_Blockx += 17.5f;
			}
		}

		g_Blockx = 0;
	}
	SetDamageblock(D3DXVECTOR3(100.0f, 2.0f, 53.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), 0);

	//�u���b�N�̏�����
	InitBlock();
	SetBlock(D3DXVECTOR3(0, 0, 172), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 9.0f, 12.0f));	//���̕�
	SetBlock(D3DXVECTOR3(172, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.8f, 9.0f, 500.0f));	//�E�̕�
	SetBlock(D3DXVECTOR3(-172, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.8f, 9.0f, 500.0f));	//���̕�
	SetBlock(D3DXVECTOR3(0, 0, -172), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 9.0f, 10.0f));	//��O�̕�

	g_gameState = GAMESTATE_NORMAL;
}

//=====================================================
//�I������
//=====================================================
void UninitGame(void)
{
	//�Q�[���X�^�[�g���S�̏I������
	UninitStartlogo();

	//�Q�[���N���A���S�̏I������
	UninitClearlogo();

	//�Q�[���I�[�o�[���S�̏I������
	UninitGameoverlogo();

	//���S�̋��E���̏I������
	UninitBorderlogo();

	//�ڂ����̏I������
	UninitBlur();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�|���S���̏I������
	UninitPolygon();

	//�o���A�̏I������
	UninitBarrier();

	//���f���̏I������
	UninitPlayer();

	//�G�̏I������
	UninitEnemy();

	////�e�̏I������
	//UninitShadow();

	//�e�̏I������
	UninitBullet();

	//�_���[�W�u���b�N�̏I������
	UninitDamageblock();

	//�u���b�N�̏I������
	UninitBlock();
}

//=====================================================
//�X�V����
//=====================================================
void UpdateGame(void)
{
	Enemy pEnemy;

	g_nCntStartState++;

	if (g_nCntStartState >= COUNT_WAIT_START_GAME)
	{
		//�Q�[���� "�N���A" or "�Q�[���I�[�o�[" ����܂ōX�V
		if (IsGameClear() == false && IsGameOver() == false)
		{
			//�J�����̍X�V����
			UpdateCamera();
			if (GetJoypadPress(4))
			{
				InitCamera();
				isCamera = true;
			}
			else
			{
				isCamera = false;
			}

			//�G�t�F�N�g�̍X�V����
			UpdateEffect();

			//�o���A�̍X�V����
			UpdateBarrier();

			//���f���̍X�V����
			UpdatePlayer();

			//�G�̍X�V����
			UpdateEnemy();

			//�e�̍X�V����
			UpdateBullet();

			//�_���[�W�u���b�N�̍X�V����
			UpdateDamageblock();

			//�u���b�N�̍X�V����
			UpdateBlock();
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCntFinishState++;
		if (g_nCntFinishState >= COUNT_WAIT_FINISH_GAME)
		{
			g_gameState = GAMESTATE_NONE;
			SetMode(MODE_RESULT);
			g_nCntStartState = 0;
			g_nCntFinishState = 0;
		}
		break;
	}
}

//=====================================================
//�`�揈��
//=====================================================
void DrawGame(void)
{
	//�J�����̐ݒ菈��
	SetCamera();

	//�o���A�̕`��
	DrawBarrier();

	//���f���̕`��
	DrawPlayer();

	//�G�̕`��
	DrawEnemy();

	////�e�̕`��
	//DrawShadow();

	//�_���[�W�u���b�N�̕`��
	DrawDamageblock();

	//�u���b�N�̕`��
	DrawBlock();

	//�|���S���̕`��
	DrawPolygon();

	//�Q�[���� "�N���A" or "�Q�[���I�[�o�[" ����܂ŕ`��
	if (IsGameClear() == false && IsGameOver() == false)
	{
		//�e�̕`��
		DrawBullet();

		//�G���G��S�ł���܂ŕ`��
		if (IsZakoDown() == false)
		{
			//if (isCamera == true)
			//{
				//�G�t�F�N�g�̕`��
				DrawEffect();
			//}
		}

	}

	if (g_nCntStartState <= COUNT_WAIT_START_GAME)
	{
		//�Q�[���X�^�[�g���S�̕`��
		DrawStartlogo();
	}

	//�Q�[���� "�N���A" or "�Q�[���I�[�o�[" ������`��
	if (IsGameClear() == true || IsGameOver() == true)
	{

		//�ڂ����̕`��
		DrawBlur();


		//�Q�[���N���A�����Ƃ�
		if (IsGameClear() == true)
		{
			//�Q�[���N���A���S�̕`��
			DrawClearlogo();

			//���S�̋��E���̕`��
			DrawBorderlogo();
		}


		//�Q�[���I�[�o�[�����Ƃ�
		if (IsGameOver() == true)
		{
			//�Q�[���I�[�o�[���S�̕`��
			DrawGameoverlogo();

			//���S�̋��E���̕`��
			DrawBorderlogo();
		}

	}
}

//=====================================================
//�ݒ菈��
//=====================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntFinishState = 0;
}

//=====================================================
//�f�o�C�X�̎擾
//=====================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}