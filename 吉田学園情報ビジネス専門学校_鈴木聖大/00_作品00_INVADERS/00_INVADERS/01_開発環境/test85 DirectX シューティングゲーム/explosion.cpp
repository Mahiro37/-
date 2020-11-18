//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "explosion.h"

//=====================================================
//�}�N����`
//=====================================================
#define MAX_EXPLOSION (128)//�����̍ő吔
#define EXPLOSION_SIZE (50)

//=====================================================
//�\���̒�`
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�F
	int nCounterAnim;//�J�E���^�[
	int nPatternAnim;//�p�^�[��NO.
	bool bUse;//�g�p���Ă��邩�ǂ���
}EXPLOSION;//�����̏��

//=====================================================
//�O���[�o���ϐ�
//=====================================================
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSION];//�����̏��

//=====================================================
//����������
//=====================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntExplosion;

	//�������̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Textures/explosion000.png", &g_pTextureExplosion);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX * MAX_EXPLOSION,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffExplosion,				// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	//�e�̐���
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)	/ �S�̂̐F
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �������_�̐F	�����x255
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �E�㒸�_�̐F	�����x255

		// �e�N�X�`�����W�̐ݒ�		��ʂɑ΂��Ă̕�����
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=====================================================
//�I������
//=====================================================
void UninitExplosion(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=====================================================
//�X�V����
//=====================================================
void UpdateExplosion(void)
{

	VERTEX_2D*pVtx;
	int nCntExplosion;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;				// �J�E���^�[���Z
			if (g_aExplosion[nCntExplosion].nCounterAnim == 3)		// 8fps�Ŏ��̃A�j���[�V����	�� �A�j���[�V�����̑���
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;			// �J�E���^�[�������l�ɖ߂�
				g_aExplosion[nCntExplosion].nPatternAnim++;				//�A�j�������̃R�}�ɂ���

				//�e�N�X�`�����W���X�V
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim == 8)	// �A�j���̃R�}���Ō�܂ōĐ����ꂽ��
				{
					g_aExplosion[nCntExplosion].bUse = false;//�������g�p���Ă��邩�̃X�C�b�`���I�t�ɂ���
				}
			}
		}
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//=====================================================
//�`�揈��
//=====================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//�������g�p���Ȃ�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, NUM_POLYGON);

			break;
		}
	}
}

//=====================================================
//�����̐ݒ�
//=====================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)//���g�p�̎�
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;//�g�p���Ă����Ԃɂ���

			//���_�J���[�̍X�V
			pVtx[0].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[1].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[2].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[3].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_SIZE / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_SIZE / 2), 0.0f);

			break;
		}

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}