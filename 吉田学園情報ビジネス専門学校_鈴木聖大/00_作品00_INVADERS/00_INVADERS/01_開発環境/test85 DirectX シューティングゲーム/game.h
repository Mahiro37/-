#ifndef _GAME_H_			// 2�d�C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

#include "main.h"

typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_MAX
}GAMESTATE;

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAMESTATE GetState(void);
void SetGameState(void);

#endif