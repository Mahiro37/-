//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "main.h"
#include "startlogo.h"
#include "input.h"
//#include "controller.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygonStartlogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonStartlogo = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
STARTLOGO g_Startlogo[MAX_STARTLOGO];

//=============================================================================
// ����������
//=============================================================================
void InitStartlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/gamestart.png", &g_pTexturePolygonStartlogo);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPolygonStartlogo,		// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPolygonStartlogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (STARTLOGO_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (STARTLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (STARTLOGO_SIZE_Y / 2), 0.0f);

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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPolygonStartlogo->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitStartlogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePolygonStartlogo != NULL)
	{
		g_pTexturePolygonStartlogo->Release();
		g_pTexturePolygonStartlogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonStartlogo != NULL)
	{
		g_pVtxBuffPolygonStartlogo->Release();
		g_pVtxBuffPolygonStartlogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStartlogo(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStartlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonStartlogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonStartlogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}

//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void SetStartlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	int nCntBlock;				// ���[�J���ϐ�

	for (nCntBlock = 0; nCntBlock < MAX_STARTLOGO; nCntBlock++)
	{
		// �u���b�N���g���ĂȂ��Ƃ�
		if (g_Startlogo[nCntBlock].bUse == false)
		{
			g_Startlogo[nCntBlock].pos = pos;
			g_Startlogo[nCntBlock].size = size;
			g_Startlogo[nCntBlock].bUse = true;
			break;
		}
	}
}