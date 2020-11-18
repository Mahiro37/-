#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY (3)//�G�̍ő吔
#define MAX_ENEMY_SIZE (100) //�G�̃T�C�Y

//================================================
//�񋓌^��`
//================================================
//�G�̏��
typedef enum
{
	ENEMYSTATE_NOMAL = 0,	//�ʏ�
	ENEMYSTATE_DAMAGE,		//�_���[�W
	ENEMYSTATE_MAX			//��Ԃ̍ő吔
}ENEMYSTATE;

//================================================
//�\���̒�`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	int nLife;			//�̗�
	ENEMYSTATE state;	//���
	int nCounterState;	//��Ԃ̃J�E���^
	int nCounterBullet;	//�e�����Ԋu
}ENEMY;


//================================================
//�v���g�^�C�v�錾
//================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, int nLife);
ENEMY*GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif