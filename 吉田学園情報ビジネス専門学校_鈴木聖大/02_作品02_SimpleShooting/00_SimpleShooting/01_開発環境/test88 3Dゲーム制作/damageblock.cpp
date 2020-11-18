//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#include "main.h"
#include "damageblock.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "game.h"
#include "effect.h"
#include "collision.h"

//=====================================================
//�}�N����`
//=====================================================
#define VALUE_MOVE (10.0f)//�|���S���̉��ړ��̑���

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDamageblock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPD3DXMESH g_pMeshDamageblock = NULL;					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatDamageblock = NULL;				//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatDamageblock = 0;							//�}�e���A�����̐�
D3DXMATRIX g_mtxWorldDamageblock;						//���[���h�}�g���b�N�X
Damageblock g_aDamageblock[MAX_DAMAGEBLOCK];			//�G�̏��
int g_IndexDamageblock = 0;
int g_nCntBillboardDamageblock = 0;

//================================================
//����������
//================================================
void InitDamageblock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("X�t�@�C��/damageblock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatDamageblock, NULL, &g_nNumMatDamageblock, &g_pMeshDamageblock);

	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		g_aDamageblock[nCntDamageblock].bUse = false;
		g_aDamageblock[nCntDamageblock].isDown = false;
		g_aDamageblock[nCntDamageblock].nLife = 3;
		g_aDamageblock[nCntDamageblock].pos = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].posOld = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].rot = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].rotDest = D3DXVECTOR3(0, 0, 0);
	}
}

//================================================
//�I������
//================================================
void UninitDamageblock(void)
{
	//���b�V���̔j��
	if (g_pMeshDamageblock != NULL)
	{
		g_pMeshDamageblock->Release();
		g_pMeshDamageblock = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatDamageblock != NULL)
	{
		g_pBuffMatDamageblock->Release();
		g_pBuffMatDamageblock = NULL;
	}
}

//================================================
//�X�V����
//================================================
void UpdateDamageblock(void)
{
	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == true)
		{
			//1F�O�̈ʒu���L��
			g_aDamageblock[nCntDamageblock].posOld = g_aDamageblock[nCntDamageblock].pos;

			for (nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
			{
				if (g_aDamageblock[nCntDamageblock].isDown == false)
				{
					//�v���C���[�̒e�ɓ���������
					if (CollisionBullet(&g_aDamageblock[nCntDamageblock].pos, &g_aDamageblock[nCntDamageblock].posOld, D3DXVECTOR3(DAMAGEBLOCK_SIZE, DAMAGEBLOCK_SIZE, DAMAGEBLOCK_SIZE + 10), BULLETTYPE_PLAYER) == true)
					{
						HitDamageblock(nCntDamageblock, 1);//(�N�ɑ΂���,���_���[�W�^���邩)
					}
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void DrawDamageblock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL*pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldDamageblock);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aDamageblock[nCntDamageblock].rot.y, g_aDamageblock[nCntDamageblock].rot.x, g_aDamageblock[nCntDamageblock].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldDamageblock, &g_mtxWorldDamageblock, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aDamageblock[nCntDamageblock].pos.x, g_aDamageblock[nCntDamageblock].pos.y, g_aDamageblock[nCntDamageblock].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldDamageblock, &g_mtxWorldDamageblock, &mtxTrans);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldDamageblock);

			//���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatDamageblock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDamageblock; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//���f���p�[�c�̕`��
				g_pMeshDamageblock->DrawSubset(nCntMat);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//�G�̎擾
//=====================================================
Damageblock*GetDamageblock(void)
{
	int nCntDamageblock;

	for (nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		return&g_aDamageblock[nCntDamageblock];
	}
	return&g_aDamageblock[nCntDamageblock];
}

//=====================================================
//�ݒ菈��
//=====================================================
void SetDamageblock(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == false)
		{
			g_aDamageblock[nCntDamageblock].pos = pos;
			g_aDamageblock[nCntDamageblock].size= size;
			g_aDamageblock[nCntDamageblock].nType = 0;
			g_aDamageblock[nCntDamageblock].bUse = true;

			break;
		}
	}
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool HitDamageblock(int nCntEnemy, int nDamage)
{
	bool bHit = false;

	g_aDamageblock[nCntEnemy].nLife -= nDamage;//�G�̗̑͂����炷

	if (g_aDamageblock[nCntEnemy].nLife <= 0)
	{
		g_aDamageblock[nCntEnemy].bUse = false;
		g_aDamageblock[nCntEnemy].isDown = true;
	}
	return bHit;
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool HitDamageblock2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ���[�J���ϐ�
	bool bHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_DAMAGEBLOCK; nCntBlock++)
	{
		// �A�C�e�����g��ꂽ��
		if (g_aDamageblock[nCntBlock].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_aDamageblock[nCntBlock].pos, g_aDamageblock[nCntBlock].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}

//=====================================================
// �u���b�N�ɉ����炠�������Ƃ��̐ݒ�
//=====================================================
bool CollisionDamageblock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ���[�J���ϐ�
	bool isHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_DAMAGEBLOCK; nCntBlock++)
	{
		// �u���b�N���g��ꂽ��
		if (g_aDamageblock[nCntBlock].bUse == true)
		{
			//�����蔻����v�Z
			if (WallCollision(pPos, pPosOld, size, &g_aDamageblock[nCntBlock].pos, g_aDamageblock[nCntBlock].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}