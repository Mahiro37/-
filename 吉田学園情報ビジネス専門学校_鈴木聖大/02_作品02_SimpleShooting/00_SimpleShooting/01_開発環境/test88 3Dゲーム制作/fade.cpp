////=============================================================================
////
//// DirectX STG enemy�̒ǉ� [fade.cpp]
//// Author :���R ���
////
////=============================================================================
//#include "main.h"
//#include "fade.h"
//
////=============================================================================
//// �O���[�o���ϐ�
////=============================================================================
//LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//���_�o�b�t�@�ւ̃|�C���^
//
//FADE g_fade;//�t�F�[�h���
//MODE g_modeNext = MODE_TITLE;//���̉��(���[�h)
//D3DXCOLOR g_colorFade;//�t�F�[�h�F
//
////=============================================================================
//// ����������
////=============================================================================
//void InitFade(MODE modeNext)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//
//	//���_�o�b�t�@����
//	pDevice->CreateVertexBuffer(
//		sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
//		D3DUSAGE_WRITEONLY,//(�Œ�)
//		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,//(�Œ�)
//		&g_pVtxBuffFade,//�ϐ������ς��ƕύX���K�v
//		NULL);
//
//	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
//
//	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����
//
//	//���_���W�̐ݒ�(�E���Őݒ�)
//	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
//
//	//rhw�̐ݒ�(�l��1.0�ŌŒ�)
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//
//	//���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	//(r,g,b,a)��0�`255�͈̔͂Ō��߂邱��
//	//r:���b�h g:�O���[�� b:�u���[ a:�����x ��\���Ă���
//
//	//�e�N�X�`�����W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//	//���_�f�[�^���A�����b�N����
//	g_pVtxBuffFade->Unlock();
//
//	g_fade = FADE_OUT;
//	g_modeNext = modeNext;
//	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�������(�s����)
//
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void UninitFade(void)
//{
//	////�e�N�X�`���̊J��
//	//if (g_pTextureFade != NULL)
//	//{
//	//	g_pTextureFade->Release();
//	//	g_pTextureFade = NULL;
//	//}
//	////���_�o�b�t�@�̊J��
//	//if (g_pVtxBuffFade != NULL)
//	//{
//	//	g_pVtxBuffFade->Release();
//	//	g_pTextureFade = NULL;
//	//}
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void UpdateFade(void)
//{
//	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
//
//					//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����
//
//	if (g_fade != FADE_NONE)
//	{//�t�F�[�h������
//		if (g_fade == FADE_IN)
//		{//�t�F�[�h�C������
//			g_colorFade.a -= FADE_RATE;//a�l�����Z���Č��̉�ʂ𕂂��オ�点��
//			if (g_colorFade.a <= 0.0f)
//			{
//				//�t�F�[�h�I������
//				g_colorFade.a = 0.0f;
//				g_fade = FADE_NONE;
//			}
//		}
//		else if (g_fade == FADE_OUT)
//		{//�t�F�[�h�A�E�g����
//			g_colorFade.a += FADE_RATE;//a�l�����Z���Č��̉�ʂ������Ă���
//			if (g_colorFade.a >= 1.0f)
//			{
//				//�t�F�[�h�C������
//				g_colorFade.a = 1.0f;
//				g_fade = FADE_IN;
//
//				//���[�h��ݒ�
//				SetMode(g_modeNext);
//			}
//		}
//		//���_�J���[�̍X�V
//		pVtx[0].col = g_colorFade;
//		pVtx[1].col = g_colorFade;
//		pVtx[2].col = g_colorFade;
//		pVtx[3].col = g_colorFade;
//	}
//	//���_�f�[�^���A�����b�N����
//	g_pVtxBuffFade->Unlock();
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void DrawFade(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
//	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, 0);
//
//	//�|���S���̕`��
//	pDevice->DrawPrimitive(
//		D3DPT_TRIANGLESTRIP,
//		0,
//		NUM_PLAYER);
//}
//
////=============================================================================
//// �t�F�[�h�̏�Ԑݒ�
////=============================================================================
//void SetFade(MODE modeNext)
//{
//	g_fade = FADE_OUT;
//	g_modeNext = modeNext;
//	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//�������(����)
//}
//
////=============================================================================
//// �t�F�[�h�̏�Ԏ擾
////=============================================================================
//FADE GetFade(void)
//{
//	return g_fade;
//}