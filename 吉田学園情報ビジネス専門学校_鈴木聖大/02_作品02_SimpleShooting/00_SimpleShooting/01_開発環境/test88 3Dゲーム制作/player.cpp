//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#include "main.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "wallblock.h"
#include "game.h"
#include "controller.h"
#include "damageblock.h"
#include "collision.h"
#include "enemy.h"
#include "barrier.h"

//================================================
//�O���[�o���ϐ�
//================================================
LPD3DXMESH g_pMeshPlayer = NULL;		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatPlayer = 0;				//�}�e���A�����̐�
Player g_aPlayer;						//���@�̏��
D3DXMATRIX g_mtxWorldPlayer;			//���[���h�}�g���b�N�X
int g_Index;
int g_nCntBulletPulse;					//�A�˂̊Ԋu
bool isGameOver;						//�Q�[���I�[�o�[�̔���
int g_nCntTime;

//================================================
//����������
//================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("X�t�@�C��/player.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);

	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.4f, -30.0f);//�����ʒu
	g_aPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0, 0, 0);//��������
	isGameOver = false;
	g_nCntBulletPulse = 0;
	g_nCntTime = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer.bUse = true;
		g_aPlayer.nLife = 3;
	}

	g_Index = SetShadow(g_aPlayer.pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_aPlayer.rot);
}

//================================================
//�I������
//================================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//================================================
//�X�V����
//================================================
void UpdatePlayer(void)
{
	float PlayerSpeed = 1.5f;//���f���̈ړ��X�s�[�h

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer.bUse == true)
		{
			//�J���������擾����
			Camera*camera = GetCamera();

			//1F�O�̈ʒu���L��
			g_aPlayer.posOld = g_aPlayer.pos;
			//g_aPlayer.rotDest = g_aPlayer.rot;

			//�R���g���[���[�̏����擾
			DIJOYSTATE2 Controller = GetController();

			if (Controller.lY != 0 || Controller.lX != 0)
			{
				float fAngle = atan2(Controller.lX, Controller.lY*-1.0f);//�X�e�B�b�N�̊p�x�����߂�A�ړ���������̊p�x

				//�X�e�B�b�N�ɂ��L�����̈ړ�
				g_aPlayer.pos.x += sinf((camera->rot.y + fAngle)) * PlayerSpeed;
				g_aPlayer.pos.z += cosf((camera->rot.y + fAngle)) * PlayerSpeed;
			}

			if (Controller.lRz != 0 || Controller.lZ != 0)
			{
				float fPlayerAngle = atan2(Controller.lZ*-1.0f, Controller.lRz);//�X�e�B�b�N�̊p�x�����߂�A�v���C���[�̊p�x

				//�X�e�B�b�N�ɂ��L�����̌����ύX
				g_aPlayer.rot.y = camera->rot.y + fPlayerAngle + D3DXToRadian(180);
			}

			////�O�㍶�E�Ƀ��f�����ړ�������
			//if (GetKeyboardPress(DIK_UP) || Controller.lY < 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//}
			//if (GetKeyboardPress(DIK_DOWN) || Controller.lY > 0)
			//{
			//	g_aPlayer.pos.x -= sinf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//	g_aPlayer.pos.z -= cosf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//}
			//if (GetKeyboardPress(DIK_RIGHT) || Controller.lX > 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y + 90))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y + 90))*PlayerSpeed;

			//}
			//if (GetKeyboardPress(DIK_LEFT) || Controller.lX < 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y - 90))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y - 90))*PlayerSpeed;
			//}

			//�O�㍶�E�Ƀ��f������������
			/*if (GetKeyboardPress(DIK_I) || Controller.lRz < 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y);
			}
			if (GetKeyboardPress(DIK_K) || Controller.lRz > 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(180));
			}
			if (GetKeyboardPress(DIK_L) || Controller.lZ > 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(90));
			}
			if (GetKeyboardPress(DIK_J) || Controller.lZ < 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(270));
			}*/

			//g_aPlayer.rot = (g_aPlayer.rotDest - g_aPlayer.rot)*0.2;


			//�e����o����
			if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadPress(5))
			{
				g_nCntBulletPulse++;

				if (g_nCntBulletPulse == 5)
				{
					SetBullet(D3DXVECTOR3(g_aPlayer.pos.x + sinf((g_aPlayer.rot.y)) * 5, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf((g_aPlayer.rot.y)) * 5), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
						D3DXVECTOR3(sinf(g_aPlayer.rot.y) * 5, 0.0f, cosf(g_aPlayer.rot.y) * 5), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_PLAYER);
					g_nCntBulletPulse = 0;
				}
			}

				//�G�̒e�ɓ���������
				if (CollisionBullet(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), BULLETTYPE_ENEMY1) == true)
				{
					HitPlayer(nCntPlayer, 1);//(�N�ɑ΂���,���_���[�W�^���邩)

				}

				//�G�̒e�ɓ���������
				if (CollisionBullet(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), BULLETTYPE_ENEMY2) == true)
				{
					HitPlayer(nCntPlayer, 1);//(�N�ɑ΂���,���_���[�W�^���邩)
				}
				
				//�G�ɓ���������
				if (CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z)) == true)
				{
					HitPlayer(nCntPlayer, 3);//(�N�ɑ΂���,���_���[�W�^���邩)
				}
			}

			for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
			{
				if (RectangleCollision(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z),
					&GetBlock()[nCount].pos, GetBlock()[nCount].size) == true)
				{ //�u���b�N�ɓ���������
					g_aPlayer.pos = g_aPlayer.posOld;
				}
			}
			//CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
			CollisionDamageblock(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
			CollisionBarrier(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X+25, PLAYER_SIZE_Y, PLAYER_SIZE_Z+30));

			SetPositionShadow(g_Index, g_aPlayer.pos, g_aPlayer.rot);
	}
}

//================================================
//�`�揈��
//================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL*pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer.bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldPlayer);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.rot.y, g_aPlayer.rot.x, g_aPlayer.rot.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer.pos.x, g_aPlayer.pos.y, g_aPlayer.pos.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

			//���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//���f���p�[�c�̕`��
				g_pMeshPlayer->DrawSubset(nCntMat);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//�G�̎擾
//=====================================================
Player*GetPlayer(void)
{
	return&g_aPlayer;
}

//=====================================================
//�_���[�W����
//=====================================================
void HitPlayer(int nCntPlayer, int nDamage)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_aPlayer.nLife -= nDamage;//�G�̗̑͂����炷

	if (g_aPlayer.nLife == 2)
	{
		D3DXLoadMeshFromX("X�t�@�C��/Player damage1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);
	}

	if (g_aPlayer.nLife == 1)
	{
		D3DXLoadMeshFromX("X�t�@�C��/Player damage2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);
	}

	if (g_aPlayer.nLife <= 0)
	{
		g_aPlayer.bUse = false;
		isGameOver = true;
		SetGameState(GAMESTATE_END);

		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));
	}
}

//=====================================================
// �N���A���菈��
//=====================================================
bool IsGameOver()
{
	return isGameOver;
}