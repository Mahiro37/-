//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//=====================================================
//�}�N����`
//=====================================================
#define MAX_BULLET (128)//�e�̍ő吔
#define BULLET_SIZE (50)

//================================================
//�\���̒�`
//================================================
//�G�̏��
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,		//�G�̒e
	BULLETTYPE_MAX			//�e�̎�ސ�
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	BULLETTYPE state;
	int nLife;			//�̗�
	int nCounterState;	//��Ԃ̃J�E���^
}BULLET;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col);	//(���ˈʒu,����,�^�C�v,�F)

#endif