//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "main.h"
#include "effect.h"
#include "input.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;			// �A�j���[�V�����J�E���^�[
int g_nPatternAnim;			// �A�j���[�V�����p�^�[��No.
int g_aNumPlayer; 
EFFECT g_Effect[MAX_EFFECT];

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	int nCntEffect = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Effect[nCntEffect].bUse = true;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/barriereffect.png", &g_pTextureEffect);
	//D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/player.png", &g_pTextureEffect);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffEffect,		// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);

	// rhw�̐ݒ�(�l��1.0�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_Effect[nCntEffect].pos = D3DXVECTOR3(EFFECT_POS_X, EFFECT_POS_Y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntEffect = 0;

	g_nCounterAnim++;				// �J�E���^�[���Z

	if (g_nCounterAnim == 4)		// 8fps�Ŏ��̃A�j���[�V����	�� �A�j���[�V�����̑���
	{
		g_nCounterAnim = 0;			// �J�E���^�[�������l�ɖ߂�
		g_nPatternAnim++;

		if (g_nPatternAnim == 10)	// �����������摜�̖���
		{
			g_nPatternAnim = 0;		// �J�E���^�[�������n�ɖ߂�
		}
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f, -1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f + 0.1f, -1.0f);

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_POS_Y / 2) - 80.0f, 0.0f);

	//pVtx += 4;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}

////=============================================================================
//// �G�t�F�N�g�̐ݒ�
////=============================================================================
//void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size)
//{
//	int nCntBlock;				// ���[�J���ϐ�
//
//	for (nCntBlock = 0; nCntBlock < MAX_EFFECT; nCntBlock++)
//	{
//		// �u���b�N���g���ĂȂ��Ƃ�
//		if (g_Effect[nCntBlock].bUse == false)
//		{
//			g_Effect[nCntBlock].pos = pos;
//			g_Effect[nCntBlock].size = size;
//			g_Effect[nCntBlock].bUse = true;
//			break;
//		}
//	}
//}