//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef PLAYER_H_
#define PLAYER_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"

//================================================
//�}�N����`
//================================================
#define PLAYER_SIZE_X (20.0f)
#define PLAYER_SIZE_Y (20.0f)
#define PLAYER_SIZE_Z (20.0f)
#define MAX_PLAYER (1)

//================================================
//�\���̒�`
//================================================
typedef struct
{
	int nType;					//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//�̗�
	int nCounterState;			//��Ԃ̃J�E���^
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 posOld;			//�ʒu���
	D3DXVECTOR3 rot;			//!<�����擾�p
	D3DXVECTOR3 rotDest;		//�ړI�̊p�x
	//D3DXVECTOR3 vecU;			//!<������x�N�g��
	//D3DXMATRIX mtxProjection;	//!<�v���W�F�N�V�����}�g���b�N�X
	//D3DXMATRIX mtxView;		//!<�r���[�}�g���b�N�X
	//float fDistance;			//!<���_-�����_�̋���
}Player;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player*GetPlayer(void);
void HitPlayer(int nCntPlayer, int nDamage);
bool IsGameOver();

#endif