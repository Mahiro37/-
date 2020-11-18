//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _STARTLOGO_H_
#define _STARTLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define MAX_STARTLOGO (1)
#define STARTLOGO_SIZE_X (1280)		// X���W�̑傫��
#define STARTLOGO_SIZE_Y (720)		// Y���W�̑傫��

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
}STARTLOGO;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitStartlogo(void);
void UninitStartlogo(void);
void UpdateStartlogo(void);
void DrawStartlogo(void);
void SetStartlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif