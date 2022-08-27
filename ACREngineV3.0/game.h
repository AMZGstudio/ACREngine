#pragma once
#include <math.h>

#define TILE_W 12
typedef struct gameData {
	int lw, lh;
	float cameraX;
	float cameraY;
	screenData* sd;
	Area levelOne;

	float playerX;
	float playerY;	
	float playerVX;
	float playerVY;

	bool playerOnGround;
} gameData;

Area loadLevel(char* data, int dw, int dh)
{
	Area wall = loadSprite("../Sprites/wall.acre");
	Area floor = loadSprite("../Sprites/floor.acre");

	Area a = createArea(TILE_W * dw, TILE_W * dh, Default, Black);
	for(int x = 0; x<dw; x++)
		for (int y = 0; y < dh; y++)
		{
			char val = data[y * dw + x];
			switch (val)
			{
			case 'w': sysDrawArea(x * TILE_W, y * TILE_W, a, wall); break;
			case 'f': sysDrawArea(x * TILE_W, y * TILE_W, a, floor); break;
			case '.': break;
			}
		}
	return a;
}

gameData initalizeGame(screenData* sd)
{
	gameData g;
	char* data = 
		"............................."
		"............................."
		"............................."
		".....wwwwwwwwwwwwwwwwwww....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wfffffffffffffffffw....."
		".....wwwwwwwwwwwwwwwwwww....."
		"............................."
		"............................."
		".............................";
	g.lw = 29;
	g.lh = 17;
	g.sd = sd;
	g.playerX = 10;
	g.playerY = 5;
	g.playerVX = 0;
	g.playerVY = 0;
	g.playerOnGround = false;
	g.cameraX = 0;
	g.cameraY = 0;
	g.levelOne = loadLevel(data, 29, 17);

	return g;
}

//
//char getTile(gameData* gd, int x, int y)
//{
//	return (x >= 0 && x < gd->lw&& y >= 0 && y < gd->lh) ? gd->val[y * gd->lw + x] : 0;
//}
void gameCalculations(gameData* gd)
{
	gd->playerVY = 0;
	gd->playerVX = 0;
	// input
	if (key(W).held) gd->playerVY = -6;
	if (key(S).held) gd->playerVY = 6;
	if (key(A).held) gd->playerVX = -6;
	if (key(D).held) gd->playerVX = 6;

	gd->playerVY = clamp(gd->playerVY, -100, 100);
	gd->playerVX = clamp(gd->playerVX, -10, 10);
	
	// player moving
	float newPlayerX = gd->playerX + timePerSec(gd->playerVX);
	float newPlayerY = gd->playerY + timePerSec(gd->playerVY);

	// check for collision
	/*if (gd->playerVX <= 0)
	{
		if (getTile(gd, newPlayerX, gd->playerY) == 'w' || getTile(gd, newPlayerX, gd->playerY + 0.9) == 'w')
			newPlayerX = (int)newPlayerX + 1, gd->playerVX = 0;
	}
	else
	{
		if (getTile(gd, newPlayerX+1, gd->playerY) == 'w' || getTile(gd, newPlayerX+1, gd->playerY + 0.9) == 'w')
			newPlayerX = (int)newPlayerX, gd->playerVX = 0;
	}
	if (gd->playerVY <= 0)
	{
		if (getTile(gd, newPlayerX, newPlayerY) == 'w' || getTile(gd, newPlayerX+0.9, newPlayerY) == 'w')
			newPlayerY = (int)newPlayerY + 1, gd->playerVY = 0;
	}
	else
	{
		if (getTile(gd, newPlayerX, newPlayerY + 1) == 'w' || getTile(gd, newPlayerX + 0.9, newPlayerY + 1) == 'w')
			newPlayerY = (int)newPlayerY, gd->playerVY = 0, gd->playerOnGround = true;
		
	}*/

	gd->playerX = newPlayerX;
	gd->playerY = newPlayerY;

	if (key(Right).pressed)
		(gd->cameraX)++;
	if (key(Down).pressed)
		(gd->cameraY)++;

	if(gd->sd->fadeEnd)
		sysDrawPartialArea(0, 0, Screen, gd->levelOne, gd->cameraX, gd->cameraY, gd->cameraX+Screen.width, gd->cameraY + Screen.height);
	else
		sysDrawPartialArea(0, 0, gd->sd->area, gd->levelOne, gd->cameraX, gd->cameraY, gd->cameraX + Screen.width, gd->cameraY + Screen.height);
	// draw map
	/*int startTileX = (int)(gd->cameraX/TILE_W);
	int startTileY = (int)(gd->cameraY/TILE_W);

	int endTileX = startTileX + (gd->cameraW / TILE_W)+1;
	int endTileY = startTileY + (gd->cameraH / TILE_W)+1;*/


	/*for (int x = startTileX; x<endTileX; x++)
		for (int y = startTileY; y < endTileY; y++)
		{

		}*/

	//int amntVisibleTilesX = ((float)Width(gd->sd->area) / (float)TILE_W);// +(Width(gd->sd->area) % TILE_W != 0) ? 1 : 0;
	//int amntVisibleTilesY = ((float)Height(gd->sd->area) / (float)TILE_W);// +(Height(gd->sd->area) % TILE_W != 0) ? 1 : 0;

	//float offsetX = clamp(gd->cameraX - (float)amntVisibleTilesX / 2.0f, 0, gd->lw - amntVisibleTilesX);
	//float offsetY = clamp(gd->cameraY - (float)amntVisibleTilesY / 2.0f, 0, gd->lh - amntVisibleTilesY);

	//float tileOffsetX = offsetX - (int)offsetX;
	//float tileOffsetY = offsetY - (int)offsetY;

	//for (int x = -1; x < amntVisibleTilesX+1; x++)
	//	for (int y = -1; y < amntVisibleTilesY+1; y++)
	//	{
	//		char c = getTile(gd, x + offsetX, y + offsetY);
	//		switch (c)
	//		{
	//		case 'f': sysDrawRect((x - tileOffsetX) * TILE_W, (y - tileOffsetY) * TILE_W, ((x - tileOffsetX) + 1) * TILE_W, ((y - tileOffsetY) + 1) * TILE_W, gd->sd->area, Default, true, Default, Brown); break;
	//		case 'w': sysDrawRect((x - tileOffsetX) * TILE_W, (y - tileOffsetY) * TILE_W, ((x - tileOffsetX) + 1) * TILE_W, ((y - tileOffsetY) + 1) * TILE_W, gd->sd->area, Default, true, Default, DarkGrey); break;
	//		default: break;
	//		}
	//	}
	//// draw player

	//sysDrawRect((gd->playerX - offsetX) * TILE_W, (gd->playerY - offsetY) * TILE_W, ((gd->playerX + 1) - offsetX) * TILE_W, ((gd->playerY + 1) - offsetY) * TILE_W, gd->sd->area, Default, false, Default, Green);

}