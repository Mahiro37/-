//=====================================================
//
// 3D�Q�[�� �u���b�N�̏��� [block.h]
// Author:�����D�l
//
//=====================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"

//=====================================================
// �}�N����`
//=====================================================
#define MAX_BARRIER (1)
#define BARRIER_SIZE_X (28)		// X���W�̑傫��
#define BARRIER_SIZE_Y (28)		// Y���W�̑傫��
#define BARRIER_SIZE_Z (28)		// Z���W�̑傫��

//=====================================================
// �\���̒�`
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;				// ���݂̈ʒu
	D3DXVECTOR3 rot;				// ���݂̊p�x
	D3DXVECTOR3 size;				// �傫��
	D3DXMATRIX mtxWorld;			// �s��v�Z�p
	LPD3DXMESH pMeshBarrierz;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBarrier;	// �}�e���A�����ւ̃|�C���^
	DWORD nNumMatBarrier;			// �}�e���A�����̐�
	bool bUse;						// �g���Ă��邩
	bool isDown;
	int nLife;						//�̗�

}BARRIER;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitBarrier(void);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
void SetBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);
bool CollisionBarrier(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool HitBarrier(int nCntEnemy, int nDamage);
bool HitBarrier2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
BARRIER*GetBarrier(void);

#endif