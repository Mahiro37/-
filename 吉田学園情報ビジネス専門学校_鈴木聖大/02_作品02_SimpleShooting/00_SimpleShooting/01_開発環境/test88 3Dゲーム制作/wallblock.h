//=====================================================
//
// 3D�Q�[�� �u���b�N�̏��� [block.h]
// Author:�����D�l
//
//=====================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include "main.h"

//=====================================================
// �}�N����`
//=====================================================
#define MAX_BLOCK (4)
#define BLOCK_SIZE_X (80)		// X���W�̑傫��
#define BLOCK_SIZE_Y (80)		// Y���W�̑傫��
#define BLOCK_SIZE_Z (80)		// Z���W�̑傫��

//=====================================================
// �\���̒�`
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;				// ���݂̈ʒu
	D3DXVECTOR3 rot;				// ���݂̊p�x
	D3DXVECTOR3 size;				// �傫��
	D3DXMATRIX mtxWorld;			// �s��v�Z�p
	LPD3DXMESH pMeshBlockz;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBlock;		// �}�e���A�����ւ̃|�C���^
	DWORD nNumMatBlock;				// �}�e���A�����̐�
	bool bUse;						// �g���Ă��邩
}BLOCK;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool HitBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
BLOCK*GetBlock(void);

#endif