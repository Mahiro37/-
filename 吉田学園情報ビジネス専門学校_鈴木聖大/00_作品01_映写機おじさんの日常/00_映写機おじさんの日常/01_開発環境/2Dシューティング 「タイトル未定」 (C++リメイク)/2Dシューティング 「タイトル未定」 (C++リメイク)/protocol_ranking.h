//=============================================================================
//
// タッチナンバーゲームの通信プロトコル定義 [protocol_ranking.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

//=============================================================================
// ■ 通信プロトコルデータフォーマット ■
// ・ランキング一覧取得
// ・ランキング設定
//=============================================================================

//=============================================================================
// ■■ ランキング一覧取得 ■■
// 
// ■■■ [Client -> Server] ■■■
// [1バイト目] コマンド (COMMAND_TYPE_GET_RANKING)
// 
// ■■■ [Client <- Server] ■■■
// [1バイト目〜4バイト目] ランキング1位のスコア
// [5バイト目〜8バイト目] ランキング2位のスコア
// …
// [37バイト目〜40バイト目] ランキング10位のスコア
//=============================================================================
//=============================================================================
// ■■ ランキング設定 ■■
// 
// ■■■ [Client -> Server] ■■■
// [1バイト目] コマンド (COMMAND_TYPE_SET_RANKING)
// [2バイト目〜5バイト目] スコア
// 
// ■■■ [Client <- Server] ■■■
// [1バイト目] ランクインした場合は順位、それ以外は 0
//=============================================================================

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_RANKING		(10)				//ランキングデータ数
#define IP_ADDRESS		"52.185.170.40"		//IPアドレス

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CProtocolRanking
{
public:
	//ランキングの構造体
	typedef struct
	{
		int nScore;	//スコア
	} RankingData;

	//ランキング通信の列挙型
	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_GET_RANKING,		// ランキング一覧を取得
		COMMAND_TYPE_SET_RANKING		// ランキングを設定
	} COMMAND_TYPE;
};

#endif