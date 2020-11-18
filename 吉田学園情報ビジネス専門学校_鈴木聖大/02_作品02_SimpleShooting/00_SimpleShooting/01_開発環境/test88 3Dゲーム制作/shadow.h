//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef SHADOW_H_
#define SHADOW_H_

#define CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_SHADOW (1)			//�e�̍ő吔
#define SHADOW_SIZE_X (10.5)	//�e�̉���
#define SHADOW_SIZE_Y (17)		//�e�̏c��

//================================================
//�\���̒�`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu���
	D3DXVECTOR3 rot;//��]���
	D3DXMATRIX mtxWorld;//�s��v�Z�p
	bool use;//�g�p����
}Shadow;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitShadow(void);
void UninitShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DrawShadow(void);

#endif