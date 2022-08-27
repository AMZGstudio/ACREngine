#pragma once

#include "screen.h"

#include "menu.h"
#include "game.h"

enum states {MENU_STATE, GAME_STATE, OPTIONS_STATE, CREDITS_STATE, EXIT_STATE};

typedef struct gameState
{
	int state;
} gameState;

void menuStateActions(gameState* gs, menuData* md)
{
	menuCalculations(md);

	if (key(Enter).pressed || key(Spacebar).pressed)
		startFade(md->s);

	if (md->s->fadeEnd)
	{
		gs->state = md->selectedOption + 1;
		startReverseFade(md->s);
	}
}

void gameStateActions(gameData* gd)
{
	gameCalculations(gd);
}