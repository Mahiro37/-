//=============================================================================
//
// スコア結果処理 [ScoreScreen.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ScoreScreen.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "bg.h"
#include "fade.h"
#include "score.h"
#include "score_attack.h"
#include "protocol_ranking.h"
#include "ui.h"
#include "time.h"
#include "ranking.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
int CScoreScreen::m_nScore = 0;
int CScoreScreen::m_nTotalTime = 0;
int CScoreScreen::m_nRanking = 0;
int CScoreScreen::m_nScoreBonus = 0;
int CScoreScreen::m_nPlayerLife = 0;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CScoreScreen::CScoreScreen()
{
	memset(m_pScore, 0, sizeof(m_pScore));
	m_nTotalScore = 0;
	m_fAddNum = 0;
	memset(m_bSet, false, sizeof(m_bSet));
	m_nPlayerLifeBonus = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CScoreScreen::~CScoreScreen()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CScoreScreen::Init(void)
{
	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM02);

	//背景の生成
	CBg::Create();

	//スコアスクリーンUIの生成
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::UI_TYPE_GAME_SCORE_SCREEN);

	//ゲームスコアの生成
	m_pScore[SCORE_TYPE_0] = CScore::Create(D3DXVECTOR3(850.0f, 238.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//タイムボーナスの生成
	m_pScore[SCORE_TYPE_1] = CScore::Create(D3DXVECTOR3(850.0f, 308.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//残機ボーナスの生成
	m_pScore[SCORE_TYPE_2] = CScore::Create(D3DXVECTOR3(850.0f, 381.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//総合スコアの生成
	m_pScore[SCORE_TYPE_3] = CScore::Create(D3DXVECTOR3(850.0f, 470.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f), 35.0f, 0, CNumber::TYPE_1);

	//タイムボーナスの計算
	double dScoreBonus = ((double)m_nTotalTime / TIME_START_NUM);
	if (dScoreBonus < 1.0)
	{
		dScoreBonus = 0.0;
	}
	double dScoreBonusNum = m_nScore * dScoreBonus;
	if (dScoreBonusNum - (int)dScoreBonusNum >= 0.5)
	{
		dScoreBonusNum += 1;
	}
	m_nScoreBonus = (int)dScoreBonusNum;

	//残機ボーナスの計算
	if (m_nPlayerLife > 0)
	{
		double dPlayerLifeBonus = ((double)m_nPlayerLife / 10) + 1;

		dPlayerLifeBonus = m_nScore * dPlayerLifeBonus;

		if (dPlayerLifeBonus - (int)dPlayerLifeBonus >= 0.5)
		{
			dPlayerLifeBonus += 1;
		}

		m_nPlayerLifeBonus = (int)dPlayerLifeBonus;
	}
	else
	{
		m_nPlayerLifeBonus = 0;
	}

	//総合スコアの計算
	m_nTotalScore = m_nScoreBonus + m_nPlayerLifeBonus + m_nScore;

	//ランキングの設定
	m_nRanking = CRanking::SetRanking(m_nTotalScore);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CScoreScreen::Uninit(void)
{
	//BGMの停止
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM02);

	//SEの停止
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_RANK_IN);

	for (int nCount = 0; nCount < SCORE_TYPE_MAX; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			//スコアの終了処理
			m_pScore[nCount]->SetScore(0);
			m_pScore[nCount]->Uninit();
			m_pScore[nCount] = NULL;
		}
	}

	//全てのメモリの開放処理
	CScene::ReleaseAllOtherThanFade();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CScoreScreen::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{ //シーンの更新が止まっていないとき
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_B))
		{ //Enterキー または Bボタンを押したとき
			if (m_bSet[SCORE_TYPE_0] == false)
			{ //加算演出が終わってないとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//ゲームスコアの生成
				m_pScore[SCORE_TYPE_0]->SetScore(m_nScore);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_0] = true;
			}
			else if (m_bSet[SCORE_TYPE_1] == false)
			{ //加算演出が終わってないとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//タイムボーナスの生成
				m_pScore[SCORE_TYPE_1]->SetScore(m_nScoreBonus);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_1] = true;
			}
			else if (m_bSet[SCORE_TYPE_2] == false)
			{ //加算演出が終わってないとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//残機ボーナスの生成
				m_pScore[SCORE_TYPE_2]->SetScore(m_nPlayerLifeBonus);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_2] = true;
			}
			else if (m_bSet[SCORE_TYPE_3] == false)
			{ //加算演出が終わってないとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//総合スコアの生成
				m_pScore[SCORE_TYPE_3]->SetScore(m_nTotalScore);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_3] = true;

				if (m_nRanking > 0 && m_nRanking <= MAX_RANKING)
				{
					//SEの再生
					CManager::GetSound()->Play(CSound::SOUND_LABEL_RANK_IN);

					//ランクインUIの生成
					CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 600.0f, 0.0f), D3DXVECTOR3(700.0f, 200.0f, 0.0f), CUi::UI_TYPE_RANK_IN);
					CUi::Create(D3DXVECTOR3(380.0f, 570.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), CUi::UI_TYPE_FUKIDASHI);
					CUi* pUi = CUi::Create(D3DXVECTOR3(385.0f, 565.0f, 0.0f), D3DXVECTOR3(120.0f, 60.0f, 0.0f), (CUi::UI_TYPE)(CUi::UI_TYPE_RANKING_1 + (m_nRanking - 1)));
					pUi->SetObjType(CScene::OBJTYPE_UI_FRONT);
				}
			}
			else
			{
				//フェードの生成
				CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_SELECT);
			}
		}

		if (m_bSet[SCORE_TYPE_0] == false)
		{ //加算演出が終わってないとき
			//SEの再生
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//加算演出のカウントを進める
			m_fAddNum += ((float)m_nScore / 60);

			//ゲームスコアの生成
			m_pScore[SCORE_TYPE_0]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nScore)
			{ //加算演出のカウントがゲームスコアより大きくなったとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//ゲームスコアの生成
				m_pScore[SCORE_TYPE_0]->SetScore(m_nScore);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_0] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_1] == false)
		{ //加算演出が終わってないとき
			//SEの再生
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//加算演出のカウントを進める
			m_fAddNum += ((float)m_nScoreBonus / 60);

			//タイムボーナスの生成
			m_pScore[SCORE_TYPE_1]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nScoreBonus)
			{ //加算演出のカウントがタイムボーナスより大きくなったとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//タイムボーナスの生成
				m_pScore[SCORE_TYPE_1]->SetScore(m_nScoreBonus);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_1] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_2] == false)
		{ //加算演出が終わってないとき
			//SEの再生
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//加算演出のカウントを進める
			m_fAddNum += ((float)m_nPlayerLifeBonus / 60);

			//残機ボーナスの生成
			m_pScore[SCORE_TYPE_2]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nPlayerLifeBonus)
			{ //加算演出のカウントが残機ボーナスより大きくなったとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//残機ボーナスの生成
				m_pScore[SCORE_TYPE_2]->SetScore(m_nPlayerLifeBonus);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_2] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_3] == false)
		{ //加算演出が終わってないとき
			//SEの再生
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//加算演出のカウントを進める
			m_fAddNum += ((float)m_nTotalScore / 60);

			//総合スコアの生成
			m_pScore[SCORE_TYPE_3]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nTotalScore)
			{ //加算演出のカウントが総合スコアより大きくなったとき
				//SEの停止
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//総合スコアの生成
				m_pScore[SCORE_TYPE_3]->SetScore(m_nTotalScore);

				//カウントを初期化
				m_fAddNum = 0;

				//判定をtrueにする
				m_bSet[SCORE_TYPE_3] = true;

				if (m_nRanking > 0 && m_nRanking <= MAX_RANKING)
				{
					//SEの再生
					CManager::GetSound()->Play(CSound::SOUND_LABEL_RANK_IN);

					//ランクインUIの生成
					CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 600.0f, 0.0f), D3DXVECTOR3(700.0f, 200.0f, 0.0f), CUi::UI_TYPE_RANK_IN);
					CUi::Create(D3DXVECTOR3(380.0f, 570.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), CUi::UI_TYPE_FUKIDASHI);
					CUi* pUi = CUi::Create(D3DXVECTOR3(385.0f, 565.0f, 0.0f), D3DXVECTOR3(120.0f, 60.0f, 0.0f), (CUi::UI_TYPE)(CUi::UI_TYPE_RANKING_1 + (m_nRanking - 1)));
					pUi->SetObjType(CScene::OBJTYPE_UI_FRONT);
				}
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CScoreScreen::Draw(void)
{
}

//*****************************************************************************
//スコアの保存
//*****************************************************************************
void CScoreScreen::SaveScore(int nScore)
{
	m_nScore = nScore;
}

//*****************************************************************************
//総合タイムの保存
//*****************************************************************************
void CScoreScreen::SaveTotalTime(int nTotalTime)
{
	m_nTotalTime = nTotalTime;
}

//*****************************************************************************
//残機の保存
//*****************************************************************************
void CScoreScreen::SavePlayerLife(int nPlayerLife)
{
	m_nPlayerLife = nPlayerLife;
}