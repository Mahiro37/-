//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef CAMERA_H_
#define CAMERA_H_

#define CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//================================================
// �}�N����`
//================================================
#define CAMERA_MOVE (5)
#define CAMERA_COEFFICIENT (0.2)

//================================================
//�\���̒�`
//================================================
typedef struct
{
	D3DXVECTOR3 posV;//!<�J�����̍��W
	D3DXVECTOR3 posR;//!<�����_(���S�_)
	D3DXVECTOR3 vecU;//!<������x�N�g��
	D3DXVECTOR3 posVDest;//!<�J�����̍��W(�ړI�n)
	D3DXVECTOR3 posRDest;//!<�����_(�ړI�n)
	D3DXMATRIX mtxProjection;//!<�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//!<�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;//!<�����擾�p
	float fDistance;//!<���_-�����_�̋���
}Camera;

//================================================
//�v���g�^�C�v�錾
//================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera*GetCamera(void);

#endif