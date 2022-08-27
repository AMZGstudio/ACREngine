#pragma once
#include <math.h>

#define TILE_W 12
typedef struct gameData {
	int lw, lh;
	float cameraX;
	float cameraY;
	screenData* sd;
	Area levelOne;
	Area world;
	Area playerFront;
	Area playerBack;
	Area playerLeft;
	Area playerRight;
	float playerX;
	float playerY;	
	float playerVX;
	float playerVY;
	int pdirection;
} gameData;

Area loadLevel(Area world, int* dw, int* dh)
{
	Area wall = loadSprite("../Sprites/wall.acre");
	Area floor = loadSprite("../Sprites/floor.acre");

	Area a = createArea(TILE_W * world.width, TILE_W * world.height, Default, Black);
	for(int x = 0; x<world.width; x++)
		for (int y = 0; y < world.height; y++)
		{
			char val = world.characters[y * world.width + x];
			switch (val)
			{
			case 'w': sysDrawArea(x * TILE_W, y * TILE_W, a, wall); break;
			case 'f': sysDrawArea(x * TILE_W, y * TILE_W, a, floor); break;
			case '.': break;
			}
			//sysDrawNumber(x * TILE_W + 1, y * TILE_W + 1, a, world.colBack[y * world.width + x], 0, EightBit, Default, DarkBlue);
		}
	*dw = world.width;
	*dh = world.height;

	deleteArea(&wall);
	deleteArea(&floor);
	return a;
}

gameData initalizeGame(screenData* sd)
{
	gameData g;
	g.sd = sd;
	g.playerX = 100;
	g.playerY = 85;
	g.playerVX = 0;
	g.playerVY = 0;
	g.cameraX = 0;
	g.cameraY = 0;
	g.world = loadSprite("../Levels/levelOne.acre");

	g.levelOne = loadLevel(g.world, &g.lw, &g.lh);
	g.playerFront = loadSprite("../Sprites/botFront.acre");
	g.playerBack = loadSprite("../Sprites/botBack.acre");
	g.playerLeft = loadSprite("../Sprites/botLeft.acre");
	g.playerRight = loadSprite("../Sprites/botRight.acre");
	g.pdirection = 3;
	return g;
}

//
bool tileSolid(gameData* gd, int x, int y)
{
	if (x < 0 || x >= gd->lw || y < 0 && y >= gd->lh)
		return false;
	if (gd->world.colBack[y * gd->lw + x] == 1)
		return true;
	return false;
}

bool collision(gameData* gd, float newPlayerX, float newPlayerY)
{
	if (tileSolid(gd, ((int)(newPlayerX) / (int)TILE_W), ((int)(newPlayerY) / (int)TILE_W)) ||
		tileSolid(gd, ((int)(newPlayerX + TILE_W - 1) / (int)TILE_W), ((int)(newPlayerY) / (int)TILE_W)) ||
		tileSolid(gd, ((int)(newPlayerX) / (int)TILE_W), ((int)(newPlayerY + TILE_W - 1) / (int)TILE_W)) ||
		tileSolid(gd, ((int)(newPlayerX + TILE_W - 1) / (int)TILE_W), ((int)(newPlayerY + TILE_W - 1) / (int)TILE_W)))
			return true;
		return false;
}

float calculatePos(float requestedVelocity)
{

}
void gameCalculations(gameData* gd)
{
	// input
	if (key(W).held) gd->playerVY = -30, gd->pdirection = 1;
	if (key(S).held) gd->playerVY = 30, gd->pdirection = 3;
	if (key(A).held) gd->playerVX = -30, gd->pdirection = 2;
	if (key(D).held) gd->playerVX = 30, gd->pdirection = 4;
	
	// velocity handling
	gd->playerVX *= 0.95;
	gd->playerVY *= 0.95;
	
	if (fabs(gd->playerVX) < 1) gd->playerVX = 0;
	if (fabs(gd->playerVY) < 1) gd->playerVY = 0;

	// collision
	float newPlayerY = gd->playerY + timePerSec(gd->playerVY);
	if (!collision(gd, gd->playerX, newPlayerY))
		gd->playerY = newPlayerY;

	float newPlayerX = gd->playerX + timePerSec(gd->playerVX);
	if (!collision(gd, newPlayerX, gd->playerY))
		gd->playerX = newPlayerX;

	// player and camera positioning
	gd->cameraX = clamp(((gd->playerX + (TILE_W / 2)) - Width(Screen) / 2), 0, Width(gd->levelOne) - Width(Screen));
	gd->cameraY = clamp(((gd->playerY + (TILE_W / 2)) - Height(Screen) / 2), 0, Height(gd->levelOne) -Height(Screen));
	int px = (gd->playerX - gd->cameraX);
	int py = (gd->playerY - gd->cameraY);

	// player direction handling
	Area player;
	if (gd->pdirection == 1) player = gd->playerBack;
	if (gd->pdirection == 2) player = gd->playerLeft;
	if (gd->pdirection == 3) player = gd->playerFront;
	if (gd->pdirection == 4) player = gd->playerRight;

	if (gd->sd->fadeEnd)
	{
		sysDrawPartialArea(0, 0, Screen, gd->levelOne, gd->cameraX, gd->cameraY, gd->cameraX + Screen.width, gd->cameraY + Screen.height);
		sysDrawArea(px, py, Screen, player);
	}
	else
	{
		sysDrawPartialArea(0, 0, gd->sd->area, gd->levelOne, gd->cameraX, gd->cameraY, gd->cameraX + Screen.width, gd->cameraY + Screen.height);
		sysDrawArea(px, py, gd->sd->area, player);
	}
}