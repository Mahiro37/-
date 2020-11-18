//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "enemy.h"
#include "main.h"
#include "explosion.h"
#include "bullet.h"

//=====================================================
//�O���[�o���ϐ��錾
//=====================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̏��
int g_nDeleteCounter = 0;									//�|�����G�̐�
int g_nResultCounter = 0;									//���U���g�ɑJ�ڂ���܂ł̎���

//=====================================================
//����������
//=====================================================
void InitEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�G�̏���������
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterBullet = 0;
	}
	g_nDeleteCounter = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Textures/enemy01.png",&g_apTextureEnemy[0]);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ENEMY,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffEnemy,				// �ϐ������ς��ƕύX���K�v
		NULL);

	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)//�G�����g�p�Ȃ�
		{
			// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);

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

			pVtx += 4;
		}
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}

//=====================================================
//�I������
//=====================================================
void UninitEnemy(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=====================================================
// �X�V����
//=====================================================
void UpdateEnemy(void)
{
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p���Ȃ�
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			if (g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2) <= 0.0f)
			{
				g_aEnemy[nCntEnemy].move.x = 10.0f;
			}
			else if (g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2) >= SCREEN_WIDTH)
			{
				g_aEnemy[nCntEnemy].move.x = -10.0f;
			}

			// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);

			g_aEnemy[nCntEnemy].nCounterBullet++;

			if (g_aEnemy[nCntEnemy].nCounterBullet == 50)
			{
				SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f), D3DXVECTOR3(-5.0f, 10.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(255, 0, 1, 255));
				SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f), D3DXVECTOR3(5.0f, 10.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(255, 0, 1, 255));
				g_aEnemy[nCntEnemy].nCounterBullet = 0;
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE:

				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

				//int nDamageFinish = 100;

				g_aEnemy[nCntEnemy].nCounterState++;

				if (g_aEnemy[nCntEnemy].nCounterState == 10)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					g_aEnemy[nCntEnemy].nCounterState = 0;
				}

				break;

			case ENEMYSTATE_NOMAL:

				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}
		
		}

		pVtx += 4;
	}

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================
// �`�揈��
//=====================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	int nCntEnemy;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// �|���S���̕`��
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p���Ȃ�`��
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy*4 , NUM_POLYGON);
		}
	}
}

//=====================================================
//�G�̎擾
//=====================================================
ENEMY*GetEnemy(void)
{
	return&g_aEnemy[0];
}

//=====================================================
//�G�̐ݒ�
//=====================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, int nLife)
{
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	int nCntEnemy;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nLife = nLife;

			// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			
			break;
		}

		pVtx += 4;
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================
//�_���[�W����
//=====================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;//���_���̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nCntEnemy].nLife -= nDamage;//�G�̗̑͂����炷

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		g_aEnemy[nCntEnemy].bUse = false;

		//��������
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		g_nDeleteCounter++;

		if (g_nDeleteCounter == MAX_ENEMY)
		{
			g_nDeleteCounter = 0;

			while (1)
			{
				g_nResultCounter++;

				if (g_nResultCounter == 10000)
				{
					SetMode(MODE_RESULT);

					break;
				}
			}
		}
	}
	else
	{
		//�_���[�W��Ԃ�
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
	}

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}