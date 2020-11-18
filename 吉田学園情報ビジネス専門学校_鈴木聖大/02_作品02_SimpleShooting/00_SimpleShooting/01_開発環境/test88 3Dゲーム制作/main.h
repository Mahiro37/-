//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#ifndef MAIN_H_
#define MAIN_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include <windows.h>
//#include <stdlib.h>
//#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p("dinput.h"�̒��O�ɒ�`)
#include <dinput.h>

//================================================
//�}�N����`
//================================================
#define SCREEN_WIDTH (1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)		// �E�C���h�E�̍���
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���_���W�E�J���[�E�e�N�X�`�����W
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���W�E�@���E�J���[

//=====================================================
// ���C�u�����̃����N
//=====================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")		// ���͏����ɕK�v

//================================================
//�\���̒�`
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
	float rhw;			// ���W
}VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			// ���W
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//���[�h�̑I��
typedef enum
{
	MODE_TITLE = 0,//�^�C�g�����
	MODE_TUTORIAL,//�`���[�g���A�����
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g���
	MODE_MAX
}MODE;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif