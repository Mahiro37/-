//=====================================================
//
// 3D�Q�[�� �u���b�N�̏��� [barrier.h]
// Author:�����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "barrier.h"
#include "camera.h"
#include "player.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"

//=====================================================
// �}�N����`
//=====================================================

//=====================================================
// �O���[�o���ϐ�
//=====================================================
BARRIER g_Barrier[MAX_BARRIER];

// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBarrier = NULL;

// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBarrier = NULL;

// ���b�V�����ւ̃|�C���^
LPD3DXMESH g_pMeshBarrier = NULL;

// �}�e���A�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBarrier = NULL;

// �}�e���A�����̐�
DWORD g_nNumMatBarrier = 0;


//=====================================================
// ����������
//=====================================================
void InitBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^


	int nCntBarrier;


	// �z�񏉊���
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		g_Barrier[nCntBarrier].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].bUse = false;
		g_Barrier[nCntBarrier].bUse = false;
		g_Barrier[nCntBarrier].isDown = false;
		g_Barrier[nCntBarrier].nLife = 3;						//�G�̗̑�

	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("X�t�@�C��/barrier.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatBarrier, NULL, &g_nNumMatBarrier, &g_pMeshBarrier);
}

//=====================================================
// �I������
//=====================================================
void UninitBarrier(void)
{
	// ���b�V���̔j��
	if (g_pMeshBarrier != NULL)
	{
		g_pMeshBarrier->Release();
		g_pMeshBarrier = NULL;
	}
	// �}�e���A���̔j��
	if (g_pBuffMatBarrier != NULL)
	{
		g_pBuffMatBarrier->Release();
		g_pBuffMatBarrier = NULL;
	}
	// �e�N�X�`���̔j��
	if (g_pTextureBarrier != NULL)
	{
		g_pTextureBarrier->Release();
		g_pTextureBarrier = NULL;
	}
}

//=====================================================
// �X�V����
//=====================================================
void UpdateBarrier(void)
{
	for (int nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			////1F�O�̈ʒu���L��
			//g_Barrier[nCntBarrier].posOld = g_Barrier[nCntBarrier].pos;

			//for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
			//{
				if (g_Barrier[nCntBarrier].isDown == false)
				{
					////�v���C���[�̒e�ɓ���������
					//if (CollisionBullet(&g_Barrier[nCntBarrier].pos, &g_Barrier[nCntBarrier].posOld, D3DXVECTOR3(BARRIER_SIZE_X, BARRIER_SIZE_Y, BARRIER_SIZE_Z + 10), BULLETTYPE_PLAYER) == true)
					//{
					if (IsZakoDown() == true)
					{
						HitBarrier(nCntBarrier, 10);//(�N�ɑ΂���,���_���[�W�^���邩)
					}
					//}
				}
			//}
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void DrawBarrier(void)
{
	int nCntBarrier;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;		// ���݂̃}�e���A���ێ��p
	D3DXMATERIAL* pMat;			// �}�e���A���f�[�^�ւ̃|�C���^


	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Barrier[nCntBarrier].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale,
				g_Barrier[nCntBarrier].size.x / BARRIER_SIZE_X,
				g_Barrier[nCntBarrier].size.y / BARRIER_SIZE_Y,
				g_Barrier[nCntBarrier].size.z / BARRIER_SIZE_Z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxScale);
			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Barrier[nCntBarrier].rot.y,
				g_Barrier[nCntBarrier].rot.x,
				g_Barrier[nCntBarrier].rot.z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Barrier[nCntBarrier].pos.x,
				g_Barrier[nCntBarrier].pos.y,
				g_Barrier[nCntBarrier].pos.z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Barrier[nCntBarrier].mtxWorld);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatBarrier->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBarrier; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBarrier);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
				// ���f���p�[�c
				g_pMeshBarrier->DrawSubset(nCntMat);
			}
			// �ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
// �u���b�N�̐ݒ�
//=====================================================
void SetBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{

	int nCntBarrier;				// ���[�J���ϐ�

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// �u���b�N���g���ĂȂ��Ƃ�
		if (g_Barrier[nCntBarrier].bUse == false)
		{
			// �Ώۂ̔z��̗v�f�ɁAused��pos��size���Z�b�g

			// �u���b�N���g�p���Ă����Ԃɂ���

			g_Barrier[nCntBarrier].pos = pos;
			g_Barrier[nCntBarrier].rot = dir;
			g_Barrier[nCntBarrier].size = size;
			g_Barrier[nCntBarrier].bUse = true;
			break;
		}
	}
}

//=====================================================
// �u���b�N�ɉ����炠�������Ƃ��̐ݒ�
//=====================================================
bool CollisionBarrier(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBarrier;					// ���[�J���ϐ�
	bool isHit = false;

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// �u���b�N���g��ꂽ��
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			//�����蔻����v�Z
			if (WallCollision(pPos, pPosOld, size, &g_Barrier[nCntBarrier].pos, g_Barrier[nCntBarrier].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}

BARRIER*GetBarrier(void)
{
	return &g_Barrier[0];		// �l��Ԃ�(�n��)
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool HitBarrier(int nCntEnemy, int nDamage)
{
	bool bHit = false;

	g_Barrier[nCntEnemy].nLife -= nDamage;//�G�̗̑͂����炷

	if (g_Barrier[nCntEnemy].nLife <= 0)
	{
		g_Barrier[nCntEnemy].bUse = false;
		g_Barrier[nCntEnemy].isDown = true;
	}
	return bHit;
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool HitBarrier2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBarrier;					// ���[�J���ϐ�
	bool bHit = false;

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// �A�C�e�����g��ꂽ��
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_Barrier[nCntBarrier].pos, g_Barrier[nCntBarrier].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}