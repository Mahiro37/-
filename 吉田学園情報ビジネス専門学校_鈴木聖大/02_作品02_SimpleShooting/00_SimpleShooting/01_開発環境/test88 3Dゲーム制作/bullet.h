//=============================================================================
//
// PLASTIC TROOPERS�̏��� [bullet.h] (�G�Ǝ��@�̒e)
// Author : �㓡�T�V��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_BULLET (256)	//�e�̍ő吔
#define BULLET_SIZE (4.0f)

//=============================================================================
//�\���̒�`
//=============================================================================
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY1,		//�G�̒e(������)
	BULLETTYPE_ENEMY2,		//�G�̒e(�����Ȃ�)
	BULLETTYPE_003,		//
	BULLETTYPE_004,		//
	BULLETTYPE_005,		//
	BULLETTYPE_MAX
}BULLETTYPE;//�A�C�e���̎��

typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld; //1F�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 size;   //�傫��
	D3DXVECTOR3 dir;	//����
	D3DXMATRIX mtxWorld;//�s��v�Z�p
	BULLETTYPE type;	//���
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}BULLET;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 moveDir, int nLife, BULLETTYPE type);
BULLET*GetBullet(void);
bool CollisionBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size, BULLETTYPE type);

#endif