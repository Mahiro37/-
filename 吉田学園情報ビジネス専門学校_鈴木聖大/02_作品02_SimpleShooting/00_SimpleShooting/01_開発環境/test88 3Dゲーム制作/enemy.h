//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef ENEMY_H_
#define ENEMY_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"

//================================================
//�}�N����`
//================================================
#define MAX_ENEMY (9)		//�G�̍ő吔
#define ENEMY_SIZE (15.0f)  //�G�̃T�C�Y

//================================================
//�O���[�o���ϐ�
//================================================


//================================================
//�\���̒�`
//================================================
typedef enum//�G�̏��
{
	ENEMYSTATE_NOMAL = 0,	//�ʏ�
	ENEMYSTATE_DAMAGE,		//�_���[�W
	ENEMYSTATE_MAX			//��Ԃ̍ő吔
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 vecU;			//!<������x�N�g��
	D3DXMATRIX mtxProjection;	//!<�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//!<�r���[�}�g���b�N�X
	D3DXVECTOR3 pos;			//�ʒu���
	D3DXVECTOR3 posOld;			//�ʒu���
	D3DXVECTOR3 rot;			//!<�����擾�p
	D3DXVECTOR3 size;			// �傫��
	ENEMYSTATE state;
	float fDistance;			//!<���_-�����_�̋���
	int nType;					//���
	int nLife;					//�̗�
	int nCounterState;			//��Ԃ̃J�E���^
	bool isDown;
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nCntBillboardEnemy;		//�e���o���J�E���g
}Enemy;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy*GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int number);
void HitEnemy(int nCntEnemy, int nDamage);
bool IsGameClear();
bool IsZakoDown();
bool IsBossDown();
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif