#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _PLAYER_H_			// 2�d�C���N���[�h�t�@�C��
#define _PLAYER_H_

//=====================================================
// �}�N����`
//=====================================================
#define VALUE_MOVE (10.0f)	//�|���S���̈ړ���
#define PLAYER_POS_X (150)
#define PLAYER_POS_Y (360)

//=====================================================
//�\���̒�`
//=====================================================
typedef enum
{
	PLAYERSTATE_NOMAL = 0,	//�ʏ�
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_MAX			//��Ԃ̍ő吔
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
	int nLife;			//�̗�
	PLAYERSTATE state;	//���
	int nCounterState;	//��Ԃ̃J�E���^
	int nCounterBullet;	//�e�����Ԋu
}PLAYER;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nDamage);

#endif