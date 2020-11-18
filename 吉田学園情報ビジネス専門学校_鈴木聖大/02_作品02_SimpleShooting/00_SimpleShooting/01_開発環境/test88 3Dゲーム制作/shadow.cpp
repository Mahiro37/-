//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#include "main.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"

//================================================
//�O���[�o���ϐ�
//================================================
//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;

//�e�̈ʒu
D3DXVECTOR3 g_posShadow;

//�e�̌���
D3DXVECTOR3 g_rotShadow;

//�e�̃��[���h�}�g���b�N�X
D3DXMATRIX g_mtxWorldShadow;

//�e�̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;

//�e
Shadow g_shadow[MAX_SHADOW];

//================================================
//����������
//================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntShadow;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/shadow.png", &g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//�e�̏��̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(SHADOW_SIZE_X / 2), 0.1f, +(SHADOW_SIZE_Y / 2));
	pVtx[1].pos = D3DXVECTOR3(+(SHADOW_SIZE_X / 2), 0.1f, +(SHADOW_SIZE_Y / 2));
	pVtx[2].pos = D3DXVECTOR3(-(SHADOW_SIZE_X / 2), 0.1f, -(SHADOW_SIZE_Y / 2)-5);
	pVtx[3].pos = D3DXVECTOR3(+(SHADOW_SIZE_X / 2), 0.1f, -(SHADOW_SIZE_Y / 2)-5);

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//================================================
//�I������
//================================================
void UninitShadow(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow = 0;

	for (; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_shadow[nCntShadow].use)
		{
			g_shadow[nCntShadow].pos = pos;
			g_shadow[nCntShadow].rot = rot;
			g_shadow[nCntShadow].use = true;
			break;
		}
	}
	return nCntShadow;//�e�����Ɏg�p�����z��̃C���f�b�N�X��Ԃ�
}

//================================================
//�X�V����
//================================================
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	g_shadow[nldxShadow].pos = pos;
	g_shadow[nldxShadow].rot = rot;
}

//================================================
//�`�揈��
//================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�s��v�Z�p�̃}�g���N�X

	//���Z�����ɐݒ�(�e�͍������猸�Z���č��ɋ߂Â���)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int i = 0; i < MAX_SHADOW; i++)
	{
		if (g_shadow[i].use)
		{
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[i].rot.y, g_shadow[i].rot.x, g_shadow[i].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_shadow[i].pos.x, g_shadow[i].pos.y, g_shadow[i].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	//�����_�[�X�e�[�g�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetTexture(0, NULL);
}