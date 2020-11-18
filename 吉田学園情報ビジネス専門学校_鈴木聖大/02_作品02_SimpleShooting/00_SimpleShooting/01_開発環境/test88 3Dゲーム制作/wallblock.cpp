//=====================================================
//
// 3D�Q�[�� �u���b�N�̏��� [block.h]
// Author:�����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "wallblock.h"
#include "camera.h"
#include "player.h"
#include "collision.h"

//=====================================================
// �}�N����`
//=====================================================

//=====================================================
// �O���[�o���ϐ�
//=====================================================
BLOCK g_Block[MAX_BLOCK];

// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;

// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;

// ���b�V�����ւ̃|�C���^
LPD3DXMESH g_pMeshBlock = NULL;

// �}�e���A�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBlock = NULL;

// �}�e���A�����̐�
DWORD g_nNumMatBlock = 0;


//=====================================================
// ����������
//=====================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^


	int nCntBlock;


	// �z�񏉊���
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].bUse = false;
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("X�t�@�C��/Block.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMatBlock,NULL,&g_nNumMatBlock,&g_pMeshBlock);
}

//=====================================================
// �I������
//=====================================================
void UninitBlock(void)
{
	// ���b�V���̔j��
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}
	// �}�e���A���̔j��
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}
	// �e�N�X�`���̔j��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//=====================================================
// �X�V����
//=====================================================
void UpdateBlock(void)
{
	//// �J���������擾����
	//CAMERA *pCamera = GetCamera();

}

//=====================================================
// �`�揈��
//=====================================================
void DrawBlock(void)
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;		// ���݂̃}�e���A���ێ��p
	D3DXMATERIAL* pMat;			// �}�e���A���f�[�^�ւ̃|�C���^


	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale,
				g_Block[nCntBlock].size.x / BLOCK_SIZE_X,
				g_Block[nCntBlock].size.y / BLOCK_SIZE_Y,
				g_Block[nCntBlock].size.z / BLOCK_SIZE_Z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxScale);
			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Block[nCntBlock].rot.y,
				g_Block[nCntBlock].rot.x,
				g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans,
				g_Block[nCntBlock].pos.x,
				g_Block[nCntBlock].pos.y,
				g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);


			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBlock; nCntMat++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBlock);
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
				// ���f���p�[�c
				g_pMeshBlock->DrawSubset(nCntMat);
			}
			// �ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
// �u���b�N�̐ݒ�
//=====================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{

	int nCntBlock;				// ���[�J���ϐ�

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �u���b�N���g���ĂȂ��Ƃ�
		if (g_Block[nCntBlock].bUse == false)
		{
			// �Ώۂ̔z��̗v�f�ɁAused��pos��size���Z�b�g

			// �u���b�N���g�p���Ă����Ԃɂ���

			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].rot = dir;
			g_Block[nCntBlock].size = size;
			g_Block[nCntBlock].bUse = true;
			break;
		}
	}
}

//=====================================================
// �u���b�N�ɉ����炠�������Ƃ��̐ݒ�
//=====================================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ���[�J���ϐ�
	bool isHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �u���b�N���g��ꂽ��
		if (g_Block[nCntBlock].bUse == true)
		{
			//�����蔻����v�Z
			if (WallCollision(pPos, pPosOld, size, &g_Block[nCntBlock].pos, g_Block[nCntBlock].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}

BLOCK*GetBlock(void)
{
	return &g_Block[0];		// �l��Ԃ�(�n��)
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool HitBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ���[�J���ϐ�
	bool bHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// �A�C�e�����g��ꂽ��
		if (g_Block[nCntBlock].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_Block[nCntBlock].pos, g_Block[nCntBlock].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}