//================================================
//3D�Q�[������
//Author:��ؐ���
//================================================
#include "main.h"
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "game.h"
#include "effect.h"
#include "collision.h"

//=====================================================
//�}�N����`
//=====================================================
#define VALUE_MOVE (10.0f)//�|���S���̉��ړ��̑���

//================================================
//�O���[�o���ϐ�
//================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPD3DXMESH g_pMeshEnemy = NULL;						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy = NULL;				//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatEnemy = 0;							//�}�e���A�����̐�
D3DXMATRIX g_mtxWorldEnemy;							//���[���h�}�g���b�N�X
Enemy g_apEnemy[MAX_ENEMY];							//�G�̏��
int g_IndexEnemy = 0;
bool isGameClear;									//�Q�[���N���A�̔���
bool isZakoDown;									//�G���G�̑S�Ŕ���

//================================================
//����������
//================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("X�t�@�C��/Enemy.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatEnemy, NULL, &g_nNumMatEnemy, &g_pMeshEnemy);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_apEnemy[nCntEnemy].bUse = false;
		g_apEnemy[nCntEnemy].isDown = false;
		g_apEnemy[nCntEnemy].nLife = 10;						//�G�̗̑�
		g_apEnemy[nCntEnemy].pos = D3DXVECTOR3(0, 0, 0);		//�����ʒu
		g_apEnemy[nCntEnemy].posOld = D3DXVECTOR3(0, 0, 0);
		g_apEnemy[nCntEnemy].rot = D3DXVECTOR3(0, 0, 0);		//��������
		g_IndexEnemy = SetShadow(g_apEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_apEnemy[nCntEnemy].rot);
		g_apEnemy[nCntEnemy].nCntBillboardEnemy = 0;
	}

	isGameClear = false;
	isZakoDown = false;
}

//================================================
//�I������
//================================================
void UninitEnemy(void)
{
	//���b�V���̔j��
	if (g_pMeshEnemy != NULL)
	{
		g_pMeshEnemy->Release();
		g_pMeshEnemy = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatEnemy != NULL)
	{
		g_pBuffMatEnemy->Release();
		g_pBuffMatEnemy = NULL;
	}
}

//================================================
//�X�V����
//================================================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			g_apEnemy[nCntEnemy].nCntBillboardEnemy++;

			//1F�O�̈ʒu���L��
			g_apEnemy[nCntEnemy].posOld = g_apEnemy[nCntEnemy].pos;

			if (g_apEnemy[nCntEnemy].nCntBillboardEnemy == 120)
			{
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(2.5f, 0.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(1.5f, 0.0f, 1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(0.0f, 0.0f, 2.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(1.5f, 0.0f, -1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(0.0f, 0.0f, -2.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-1.5f, 0.0f, -1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-2.5f, 0.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-1.5f, 0.0f, 1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);

				g_apEnemy[nCntEnemy].nCntBillboardEnemy = 0;
			}

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				if (g_apEnemy[nCntEnemy].isDown == false)
				{
					//�v���C���[�̒e�ɓ���������
					if (CollisionBullet(&g_apEnemy[nCntEnemy].pos, &g_apEnemy[nCntEnemy].posOld, D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE), BULLETTYPE_PLAYER) == true)
					{
						HitEnemy(nCntEnemy, 1);//(�N�ɑ΂���,���_���[�W�^���邩)
					}
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL*pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_apEnemy[nCntEnemy].rot.y, g_apEnemy[nCntEnemy].rot.x, g_apEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTrans);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			//���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//���f���p�[�c�̕`��
				g_pMeshEnemy->DrawSubset(nCntMat);
			}

			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//�G�̎擾
//=====================================================
Enemy*GetEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		return&g_apEnemy[nCntEnemy];
	}
	return&g_apEnemy[nCntEnemy];
}

//=====================================================
//�ݒ菈��
//=====================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int number)
{
	for (number = 0; number < MAX_ENEMY; number++)
	{
		if (g_apEnemy[number].bUse == false)
		{
			g_apEnemy[number].pos = pos;
			g_apEnemy[number].nType = nType;
			g_apEnemy[number].bUse = true;

			break;
		}
	}
}

//=====================================================
//�_���[�W����
//=====================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	int Count = 0;

	g_apEnemy[nCntEnemy].nLife -= nDamage;//�G�̗̑͂����炷

	if (g_apEnemy[nCntEnemy].nLife <= 0)
	{
 		g_apEnemy[nCntEnemy].bUse = false;
		g_apEnemy[nCntEnemy].isDown = true;
	}
	else
	{
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == false)
		{
			Count++;
			if (Count >= 8)
			{
				isZakoDown = true;
			}
		}

		if (isZakoDown == true)
		{
			if (Count == 9)
			{
				isGameClear = true;
				SetGameState(GAMESTATE_END);
			}
		}

	}
}

//=====================================================
// �N���A���菈��
//=====================================================
bool IsGameClear()
{
	return isGameClear;
}

//=====================================================
// �G���I�S�Ŕ��菈��
//=====================================================
bool IsZakoDown()
{
	return isZakoDown;
}


//=====================================================
// �u���b�N�ɉ����炠�������Ƃ��̐ݒ�
//=====================================================
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntEnemy;					// ���[�J���ϐ�
	bool isHit = false;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// �u���b�N���g��ꂽ��
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			//�����蔻����v�Z
			if (WallCollision(pPos, pPosOld, size, &g_apEnemy[nCntEnemy].pos, g_apEnemy[nCntEnemy].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}