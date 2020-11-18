//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _BORDERLOGO_H_
#define _BORDERLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define MAX_BORDERLOGO (1)
#define BORDERLOGO_SIZE_X (1920)		// X���W�̑傫��
#define BORDERLOGO_SIZE_Y (1080)		// Y���W�̑傫��

//================================================
//�\���̒�`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld; //1F�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 size;   //�傫��
	D3DXMATRIX mtxWorld;//�s��v�Z�p
						//BULLETTYPE type;	//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}BORDERLOGO;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitBorderlogo(void);
void UninitBorderlogo(void);
void UpdateBorderlogo(void);
void DrawBorderlogo(void);
void SetBorderlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif