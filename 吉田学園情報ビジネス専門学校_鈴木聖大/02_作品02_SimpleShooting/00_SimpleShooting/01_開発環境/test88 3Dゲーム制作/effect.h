//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define MAX_EFFECT (1)
#define VALUE_MOVE (10.0f)		//�|���S���̈ړ���
#define EFFECT_SIZE_X (50)		// X���W�̑傫��
#define EFFECT_SIZE_Y (50)		// Y���W�̑傫��
#define	EFFECT_POS_X (180) 
#define	EFFECT_POS_Y (180) 

//================================================
//�\���̒�`
//================================================
typedef enum
{
	EFFECTTYPE_GAMECLEAR,		//�Q�[���N���A
	EFFECTTYPE_GAMEOVER,		//�Q�[���I�[�o�[
	EFFECTTYPE_002,				//
	EFFECTTYPE_003,				//
	EFFECTTYPE_004,				//
	EFFECTTYPE_005,				//
	EFFECTTYPE_MAX
}EFFECTTYPE;//�G�t�F�N�g�̎��

typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld; //1F�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 size;   //�傫��
	D3DXMATRIX mtxWorld;//�s��v�Z�p
	//BULLETTYPE type;	//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}EFFECT;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif