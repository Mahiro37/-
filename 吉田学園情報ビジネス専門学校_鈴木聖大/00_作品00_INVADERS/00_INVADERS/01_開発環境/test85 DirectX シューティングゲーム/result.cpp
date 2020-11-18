//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "player.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
//VERTEX_2D g_aVertex[NUM_VERTEX];						// ���_���i�[
LPDIRECT3DTEXTURE9 g_pTexturePolygonResult = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonResult = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();

	// �e�N�X�`���̓ǂݍ���
	if (pPlayer->bUse == true)
	{
		D3DXCreateTextureFromFile(pDevice, "Textures/gameclear.png", &g_pTexturePolygonResult);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, "Textures/gameover.png", &g_pTexturePolygonResult);
	}

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPolygonResult,		// �ϐ������ς��ƕύX���K�v
		NULL);

	VERTEX_2D * pVtx;

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffPolygonResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffPolygonResult->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePolygonResult != NULL)
	{
		g_pTexturePolygonResult->Release();
		g_pTexturePolygonResult = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonResult != NULL)
	{
		g_pVtxBuffPolygonResult->Release();
		g_pVtxBuffPolygonResult = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetMode(MODE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}