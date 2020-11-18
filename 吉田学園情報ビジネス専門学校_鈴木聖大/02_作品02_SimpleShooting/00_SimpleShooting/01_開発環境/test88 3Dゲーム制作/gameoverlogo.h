//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _GAMEOVERLOGO_H_
#define _GAMEOVERLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define MAX_GAMEOVERLOGO (1)
#define GAMEOVERLOGO_SIZE_X (1280)		// X���W�̑傫��
#define GAMEOVERLOGO_SIZE_Y (720)		// Y���W�̑傫��

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
}GAMEOVERLOGO;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitGameoverlogo(void);
void UninitGameoverlogo(void);
void UpdateGameoverlogo(void);
void DrawGameoverlogo(void);
void SetGameoverlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif