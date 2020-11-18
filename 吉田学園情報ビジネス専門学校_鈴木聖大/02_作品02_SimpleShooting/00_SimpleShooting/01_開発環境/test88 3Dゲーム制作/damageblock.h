//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef DAMAGEBLOCK_H_
#define DAMAGEBLOCK_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_DAMAGEBLOCK (68)		//�u���b�N�̍ő吔
#define DAMAGEBLOCK_SIZE (18.0f)	//�u���b�N�̃T�C�Y

//================================================
//�O���[�o���ϐ�
//================================================


//================================================
//�\���̒�`
//================================================
typedef enum//�G�̏��
{
	DAMAGEBLOCKSTATE_NOMAL = 0,	//�ʏ�
	DAMAGEBLOCKSTATE_DAMAGE,	//�_���[�W
	DAMAGEBLOCKSTATE_MAX		//��Ԃ̍ő吔
}DAMAGEBLOCKSTATE;

typedef struct
{
	D3DXVECTOR3 vecU;			//!<������x�N�g��
	D3DXMATRIX mtxProjection;	//!<�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//!<�r���[�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 posOld;			//�ʒu���
	D3DXVECTOR3 size;			// �傫��
	DAMAGEBLOCKSTATE state;
	D3DXVECTOR3 rot;			//!<�����擾�p
	D3DXVECTOR3 rotDest;		//�ړI�̊p�x
	float fDistance;			//!<���_-�����_�̋���
	int nType;					//���
	bool isDown;
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nLife;					//�̗�
	int nCounterState;			//��Ԃ̃J�E���^
}Damageblock;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitDamageblock(void);
void UninitDamageblock(void);
void UpdateDamageblock(void);
void DrawDamageblock(void);
Damageblock*GetDamageblock(void);
void SetDamageblock(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);
bool HitDamageblock(int nCntEnemy, int nDamage);
bool HitDamageblock2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool IsGameClear();
bool CollisionDamageblock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif