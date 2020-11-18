//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "bullet.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"

//=====================================================
//�\���̒�`
//=====================================================
//typedef struct
//{
//	D3DXVECTOR3 pos;//�ʒu
//	D3DXVECTOR3 move;//�ړ���
//	int nLife;//����
//	bool bUse;//�g�p���Ă��邩�ǂ���
//}BULLET;

//=====================================================
//�O���[�o���ϐ�
//=====================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
BULLET g_aBullet[MAX_BULLET];//�e�̏��
bool g_bEnemyDamage = false;

//=====================================================
//����������
//=====================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBullet;
	
	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3((BULLET_SIZE/2), (BULLET_SIZE / 2), 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 50;
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Textures/Bullet.png",&g_pTextureBullet);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BULLET,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffBullet,				// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	//�e�̐���
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)	/ �S�̂̐F
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255

		// �e�N�X�`�����W�̐ݒ�		��ʂɑ΂��Ă̕�����
		pVtx[0].tex = D3DXVECTOR2(0,0);
		pVtx[1].tex = D3DXVECTOR2(1,0);
		pVtx[2].tex = D3DXVECTOR2(0,1);
		pVtx[3].tex = D3DXVECTOR2(1,1);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=====================================================
//�I������
//=====================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	// ���_���ւ̃|�C���^		�ʒu��F������Ƃ��̍ŏ��ɓ����(&pVtx)
	VERTEX_2D *pVtx;

	ENEMY *apEnemy = GetEnemy();
	PLAYER *pPlayer = GetPlayer();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)//�e���g�p����Ă���
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			switch (g_aBullet[nCntBullet].nType)
			{
			case BULLETTYPE_PLAYER:

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (apEnemy[nCntEnemy].bUse == true)
					{
						//�����蔻��
						if (apEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2) <= g_aBullet[nCntBullet].pos.x&&
							apEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2) >= g_aBullet[nCntBullet].pos.x&&
							apEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2) <= g_aBullet[nCntBullet].pos.y&&
							apEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2) >= g_aBullet[nCntBullet].pos.y)
						{//�G�ɒe������������
							g_aBullet[nCntBullet].bUse = false;//�e�𖢎g�p��Ԃɂ���
							HitEnemy(nCntEnemy, 1);
						}
					}
				}

				break;

			case BULLETTYPE_ENEMY:

					if (pPlayer->bUse == true)
					{
						//�����蔻��(�G�ɒe������������)
						if (pPlayer->pos.x - (PLAYER_SIZE_X / 2) <= g_aBullet[nCntBullet].pos.x&&
							pPlayer->pos.x + (PLAYER_SIZE_X / 2) >= g_aBullet[nCntBullet].pos.x&&
							pPlayer->pos.y - (PLAYER_SIZE_Y / 2) <= g_aBullet[nCntBullet].pos.y&&
							pPlayer->pos.y + (PLAYER_SIZE_Y / 2) >= g_aBullet[nCntBullet].pos.y)
						{
							g_aBullet[nCntBullet].bUse = false;	//�e�𖢎g�p��Ԃɂ���
							HitPlayer(1);
							//SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
						}
					}
			}

			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);

			//��ʊO�ɏo���疢�g�p��
			if (g_aBullet[nCntBullet].pos.x < 0 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + (20 / 2))
			{
				g_aBullet[nCntBullet].nLife = 50;
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.y < 0 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].nLife = 50;
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBullet;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�e���g�p���Ȃ�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//=============================================================================
//�e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^		�ʒu��F������Ƃ��̍ŏ��ɓ����(&pVtx)
	VERTEX_2D *pVtx;

	int nCntBullet;
	
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)//�e���g�p����Ă��Ȃ��ꍇ
		{
			//�ʒu��ݒ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;//�g�p���Ă����Ԃɂ���

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y - (BULLET_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_SIZE / 2), g_aBullet[nCntBullet].pos.y + (BULLET_SIZE / 2), 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, 255);

			break;
		}

		pVtx += 4;	//���_���C���N�������g
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}