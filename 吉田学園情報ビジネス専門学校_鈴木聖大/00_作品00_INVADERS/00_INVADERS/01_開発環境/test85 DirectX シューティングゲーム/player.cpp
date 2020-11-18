//=====================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//=====================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"

//=====================================================
// �O���[�o���ϐ�
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
PLAYER g_Player;									//�v���C���[�̏��

//=====================================================
// ����������
//=====================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	g_Player.nLife = 2;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "Textures/Player.png", &g_pTexturePlayer);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPlayer,				// �ϐ������ς��ƕύX���K�v
		NULL);

	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);

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

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	g_Player.bUse = true;
}

//=====================================================
// �|���S���I������
//=====================================================
void UninitPlayer(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=====================================================
// �|���S���X�V����
//=====================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ړ��̏���
	// A�̃L�[�������ꂽ��
	if (GetKeyboardPress(DIK_A))
	{
		g_Player.pos.x -= VALUE_MOVE;	// �ړ��̑���
	}

	// W�̃L�[�������ꂽ��
	if (GetKeyboardPress(DIK_W))
	{
		g_Player.pos.y -= VALUE_MOVE;	// �ړ��̑���
	}

	// S�̃L�[�������ꂽ��
	if (GetKeyboardPress(DIK_S))
	{
		g_Player.pos.y += VALUE_MOVE;	// �ړ��̑���
	}

	// D�̃L�[�������ꂽ��
	if (GetKeyboardPress(DIK_D))
	{
		g_Player.pos.x += VALUE_MOVE;	// �ړ��̑���
	}

	//�X�y�[�X�L�[�������ꂽ��
#if 0
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Player.nCounterBullet++;

		if (g_Player.nCounterBullet == 10)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f), D3DXVECTOR3(0, -15, 0), BULLETTYPE_PLAYER, D3DXCOLOR(255, 255, 255, 255));
			g_Player.nCounterBullet = 0;
		}
	}
#elif 1
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f), D3DXVECTOR3(0, -15, 0), BULLETTYPE_PLAYER, D3DXCOLOR(255, 255, 255, 255));
	}
#endif

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y - (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE_X / 2), g_Player.pos.y + (PLAYER_SIZE_Y / 2), 0.0f);

	// �e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================
// �|���S���`�揈��
//=====================================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);//�i�v���~�e�B�u�̎�� , �O�Ԗڂ̃|�C���^ , �v���~�e�B�u�̐��j
	}
}

//=====================================================
//�_���[�W����
//=====================================================
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;//���_���̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_Player.nLife -= nDamage;//�G�̗̑͂����炷

	if (g_Player.nLife <= 0)
	{
		g_Player.bUse = false;

		//��������
		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));

		SetMode(MODE_RESULT);

		g_Player.bUse = true;
	}
	else
	{
		//�_���[�W��Ԃ�
		g_Player.state = PLAYERSTATE_DAMAGE;
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================
//�G�̎擾
//=====================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}