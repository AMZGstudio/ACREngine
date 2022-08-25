#pragma once
#include "menu.h"

#define MENU_STATE 0
#define GAME_STATE 1

typedef struct gameState
{
	int state;
} gameState;

void menuStateActions(gameState* gd, menuData* md)
{
	menuCalculations(md);

	if (key(Enter).pressed || key(Spacebar).pressed)
		startFade(md->s);

	if (md->s->fadeEnd)
	{
		gd->state = GAME_STATE;
		startReverseFade(md->s);
	}
}