//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
// main.h��bg.h�����������Ă���
#include "main.h"
#include "bg.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
//VERTEX_2D g_aVertex[NUM_VERTEX];					// ���_���i�[
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;		// �e�N�X�`���ւ̃|�C���^		Bg�ɕύX���K�v
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBg = NULL;	// ���_�o�b�t�@�ւ̃|�C���^		Bg�ɕύX���K�v
int g_nCounterAnimBg;
int g_nPatternAnimBg;

//=============================================================================
// ����������
//=============================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nCounterAnimBg = 0;
	g_nPatternAnimBg = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Textures/bg100.png",		// �t�@�C���̖��O
		&g_pTexturePolygonBg);	// �ϐ������ς��ƕύX

								// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPolygonBg,				// �ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)	/ �S�̂̐F
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	// �e�N�X�`�����W�̐ݒ�		��ʂɑ΂��Ă̕�����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPolygonBg->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonBg != NULL)
	{
		g_pVtxBuffPolygonBg->Release();
		g_pVtxBuffPolygonBg = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg(void)
{
	VERTEX_2D *pVtx;

	g_nCounterAnimBg++;

	if (g_nCounterAnimBg == 1)
	{
		g_nCounterAnimBg = 0;

		g_nPatternAnimBg++;

		if (g_nPatternAnimBg == 2000)
		{
			g_nPatternAnimBg = 0;
		}
	}

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_nPatternAnimBg * 0.996f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_nPatternAnimBg * 0.996f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_nPatternAnimBg * 0.996f + 0.996f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_nPatternAnimBg * 0.996f + 0.996f);

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffPolygonBg->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBg, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonBg);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}

/*
[����������]���_�o�b�t�@�̐��� �� ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾 �� ���_���W�̐ݒ�Frhw�̐ݒ�F���_�J���[�F�e�N�X�`�����W�̐ݒ�
[�I������]�e�N�X�`���̊J�� �� ���_�o�b�t�@�̊J��
[�X�V����]
[�`�揈��]���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h �� ���_�t�H�[�}�b�g �� �e�N�X�`���̐ݒ� �� �|���S���̕`��
*/