//=============================================================================
//
// PLASTIC TROOPERS [bullet.cpp]�̏��� (�e)
// Author:�㓡�T�V��
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"
#include "wallblock.h"
#include "barrier.h"
#include "damageblock.h"
#include "collision.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet[BULLETTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
BULLET g_Bullet[MAX_BULLET];//�A�C�e���̏��

//=============================================================================
//����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|���S���̈ʒu
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|���S���̈ړ���
		g_Bullet[nCntBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|���S���̑傫��
		g_Bullet[nCntBullet].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�|���S���̌���
		g_Bullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_Bullet[nCntBullet].nLife = 0;
		g_Bullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffBullet,//�ϐ������ς��ƕύX���K�v
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/billboard.png", &g_pTextureBullet[0]);   //�v���C���[�̒e
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/BulletType1.png", &g_pTextureBullet[1]);  //�G�̒e(������)
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/BulletType2.png", &g_pTextureBullet[2]);  //�G�̒e(�����Ȃ�)

	VERTEX_3D *pVtx;//���_���̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�i�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�f�[�^�A�����b�N
	g_pVtxBuffBullet->Unlock();

}

//=============================================================================
// �A�C�e���I������
//=============================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
	for (int nCntBullet = 0; nCntBullet < BULLETTYPE_MAX; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateBullet(void)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//1F�O�̈ʒu
			g_Bullet[nCntBullet].posOld = g_Bullet[nCntBullet].pos;

			//�ړ��ʂ𔽉f������
			g_Bullet[nCntBullet].pos += g_Bullet[nCntBullet].move;

			//�e�̎˒������߂�
			g_Bullet[nCntBullet].nLife--;

			//�e���ǂɓ���������A�e�̃��C�t���Ȃ���
			if (HitBlock(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE + 10, BULLET_SIZE))==true)
			{
				g_Bullet[nCntBullet].nLife = 0;
			}

			//�e���o���A�ɓ���������A�e�̃��C�t���Ȃ���
			if (HitBarrier2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BARRIER_SIZE_X, BARRIER_SIZE_Y + 10, BARRIER_SIZE_Z)) == true)
			{
				g_Bullet[nCntBullet].nLife = 0;
			}

			//���@�̒e���G�̃I�����W�̒e�ɓ���������A���@�̒e�̃��C�t���Ȃ���
			if (g_Bullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				if (CollisionBullet(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, g_Bullet[nCntBullet].size, BULLETTYPE_ENEMY1) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}

			//�G�̒e���u���b�N�ɓ���������A�G�̒e�̃��C�t���Ȃ���
			if (g_Bullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{
				if (HitDamageblock2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE , BULLET_SIZE +10, BULLET_SIZE )) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}
			if (g_Bullet[nCntBullet].type == BULLETTYPE_ENEMY2)
			{
				if (HitDamageblock2(&g_Bullet[nCntBullet].pos, &g_Bullet[nCntBullet].posOld, D3DXVECTOR3(BULLET_SIZE , BULLET_SIZE + 10, BULLET_SIZE )) == true)
				{
					g_Bullet[nCntBullet].nLife = 0;
				}
			}

			//���C�t���Ȃ��Ȃ����疢�g�p��
			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				g_Bullet[nCntBullet].bUse = false;	//�g�p���Ȃ���Ԃɂ���
			}

			//���_���W�̏������i�E���Őݒ肷��j
			pVtx[0].pos = D3DXVECTOR3(0.0f - g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y + g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f + g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y + g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f - g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y - g_Bullet[nCntBullet].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f + g_Bullet[nCntBullet].size.x, g_Bullet[nCntBullet].size.y - g_Bullet[nCntBullet].size.y, 0.0f);

		}
		pVtx += 4;
	}

	//���_�f�[�^���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;//�s��v�Z�p�̃}�g���N�X

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g��l�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//�A���t�@�e�X�g�̔�r���@�̐ݒ�iGREATER�͊�l���傫���ꍇ)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].mtxWorld);
			//��]�̋t�s��𐶐�
			pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
			D3DXMatrixInverse(&g_Bullet[nCntBullet].mtxWorld, NULL, &mtxRot);
			g_Bullet[nCntBullet].mtxWorld._41 = 0;//�ړ��͂��������Ȃ��̂�0����
			g_Bullet[nCntBullet].mtxWorld._42 = 0;//�ړ��͂��������Ȃ��̂�0����
			g_Bullet[nCntBullet].mtxWorld._43 = 0;//�ړ��͂��������Ȃ��̂�0����

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].mtxWorld, &g_Bullet[nCntBullet].mtxWorld, &mtxTrans);
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].mtxWorld);
			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet[g_Bullet[nCntBullet].type]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			//�e�N�X�`���̐ݒ�̉���
			pDevice->SetTexture(0, NULL);
		}
	}

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
//�o���b�g�̐ݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 moveDir, int nLife, BULLETTYPE type)
{
	int nCntBullet = 0;

	for (; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			g_Bullet[nCntBullet].bUse = true;
			g_Bullet[nCntBullet].pos = pos;
			g_Bullet[nCntBullet].dir = moveDir;
			g_Bullet[nCntBullet].size = size;
			g_Bullet[nCntBullet].move = move;
			g_Bullet[nCntBullet].nLife = nLife;
			g_Bullet[nCntBullet].type = type;

			break;
		}

	}

}

//=============================================================================
//�o���b�g�̎擾
//=============================================================================
BULLET*GetBullet(void)
{
	return &g_Bullet[0];
}

//=====================================================
// �����蔻��̐ݒ�
//=====================================================
bool CollisionBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size, BULLETTYPE type)
{
	bool bHit = false;  //�����������ǂ���

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// �e���g��ꂽ��
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//�����蔻����v�Z
			if (RectangleCollision(pPos, pPosOld, size, &g_Bullet[nCntBullet].pos, g_Bullet[nCntBullet].size) == true)
			{
				//�^�C�v�������Ȃ�
				if (g_Bullet[nCntBullet].type == type)
				{
					bHit = true;    //��������
					g_Bullet[nCntBullet].bUse = false;  //���������疢�g�p��
				}
			}
		}
	}

	return bHit;    //�����������ǂ�����Ԃ�
}