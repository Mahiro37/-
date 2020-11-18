//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#include "main.h"
#include "blur.h"

//================================================
//�O���[�o���ϐ�
//================================================
//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlur = NULL;

//�|���S���̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureBlur = NULL;

//�|���S���̈ʒu
D3DXVECTOR3 g_posBlur;

//�|���S���̌���
D3DXVECTOR3 g_rotBlur;

//�|���S���̃��[���h�}�g���b�N�X
D3DXMATRIX g_mtxWorldBlur;

//================================================
//����������
//================================================
void InitBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/blur.jpg", &g_pTextureBlur);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlur,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlur->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(BLUR_SIZE / 2), 30.0f, +(BLUR_SIZE / 2));
	pVtx[1].pos = D3DXVECTOR3(+(BLUR_SIZE / 2), 30.0f, +(BLUR_SIZE / 2));
	pVtx[2].pos = D3DXVECTOR3(-(BLUR_SIZE / 2), 30.0f, -(BLUR_SIZE / 2));
	pVtx[3].pos = D3DXVECTOR3(+(BLUR_SIZE / 2), 30.0f, -(BLUR_SIZE / 2));

	//�e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBlur->Unlock();
}

//================================================
//�I������
//================================================
void UninitBlur(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureBlur != NULL)
	{
		g_pTextureBlur->Release();
		g_pTextureBlur = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlur != NULL)
	{
		g_pVtxBuffBlur->Release();
		g_pVtxBuffBlur = NULL;
	}
}

//================================================
//�X�V����
//================================================
void UpdateBlur(void)
{
}

//================================================
//�`�揈��
//================================================
void DrawBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�s��v�Z�p�̃}�g���N�X

								//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBlur);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlur.y, g_rotBlur.x, g_rotBlur.z);
	D3DXMatrixMultiply(&g_mtxWorldBlur, &g_mtxWorldBlur, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBlur.x, g_posBlur.y, g_posBlur.z);
	D3DXMatrixMultiply(&g_mtxWorldBlur, &g_mtxWorldBlur, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlur);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlur, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlur);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}