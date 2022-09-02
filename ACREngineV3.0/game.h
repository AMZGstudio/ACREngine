#pragma once
#include <math.h>

#include "inventory.h"
#include "screen.h"

#define TILE_W 14

typedef struct entity {
	float vx;
	float vy;
	float px;
	float py;
	short facing; // Up, Down, Left, Right
	bool faceOps[4];
	Point coords[4];

	Area textures;
	int textureW;
	int textureH;
	Space boundingBox;
	
	Point* cSpr;
} entity;

typedef struct gameData {
	float cameraX;
	float cameraY;
	Area levelOne;
	Area worldData;
	Items items;

	entity player;
	entity mob;

	bool showBox;
	bool showInventory;
	
} gameData;

Area loadLevel(Area world)
{
	Area wall = loadSprite("../Sprites/wall.acre");
	Area floor = loadSprite("../Sprites/tile.acre");
	Area wallLeft = loadSprite("../Sprites/wallLeft.acre");
	Area wallRight = loadSprite("../Sprites/wallRight.acre");

	Area a = createArea(TILE_W * world.width, TILE_W * world.height, Default, Black);
	for(int x = 0; x<world.width; x++)
		for (int y = 0; y < world.height; y++)
		{
			char val = world.characters[y * world.width + x];
			switch (val)
			{
			case 'w': sysDrawArea(x * TILE_W, y * TILE_W, a, wall); break;
			case 'f': sysDrawArea(x * TILE_W, y * TILE_W, a, floor); break;
			case 'r': sysDrawArea(x * TILE_W, y * TILE_W, a, wallRight); break;
			case 'l': sysDrawArea(x * TILE_W, y * TILE_W, a, wallLeft); break;
			case '.': break;
				
			}
		}

	deleteArea(&wall);
	deleteArea(&floor);
	deleteArea(&wallLeft);
	deleteArea(&wallRight);

	return a;
}


Space calculateBoundingBox(Area ar, int w, int h)
{
	Space s;
	s.startY = h, s.endY = 0;

	bool p1HitX = false, p2HitX = false;
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			if (ar.colBack[y * ar.width + x] != Default)
			{
				if (!p1HitX)
					p1HitX = true, s.startX = x;
				if (y < s.startY)
					s.startY = y;
			}

	for (int x = w-1; x >=0; x--)
		for (int y = h-1; y >= 0; y--)
			if (ar.colBack[y * ar.width + x] != Default)
			{
				if (!p2HitX)
					p2HitX = true, s.endX = x;
				if (y > s.endY)
					s.endY = y;
			}
	return s;
}

entity createEntity(int x, int y, Area textures, int textureW, int textureH, int fx, int fy, int bx, int by, int lx, int ly, int rx, int ry)
{
	entity e;
	e.px = x, e.py = y;
	e.vx = 0, e.vy = 0;
	e.textureW = textureW;
	e.textureH = textureH;
	
	e.faceOps[0] = ((bx+by)>=0)?true:false, e.faceOps[1] = ((lx+ly)>=0)?true:false, e.faceOps[2] = ((fx+fy)>=0)?true:false, e.faceOps[3] = ((rx+ry)>=0)?true:false;
	
	e.boundingBox = calculateBoundingBox(textures, textureW, textureH);
	e.textures = textures;
	e.coords[0].x = bx, e.coords[0].y = by, e.coords[1].x = lx, e.coords[1].y = ly;
	e.coords[2].x = fx, e.coords[2].y = fy, e.coords[3].x = rx, e.coords[3].y = ry;
	e.facing = (e.faceOps[2] ? Down : (e.faceOps[0] ? Up : (e.faceOps[1] ? Left : (Right))));
	
	return e;
}

gameData initalizeGame()
{
	gameData g;
	g.cameraX = 0;
	g.cameraY = 0;
	g.showBox = !1;
	g.showInventory = !1;
	g.worldData = loadSprite("../Levels/levelOne.acre");

	g.levelOne = loadLevel(g.worldData);
	g.items = initalizeInventory(6, 3);

	g.player = createEntity(160, 160, loadSprite("../Sprites/bot.acre"), 12, 13, 1,0, 0,0, 0,1, 1,1);
	g.mob = createEntity(180, 180, loadSprite("../Sprites/oldMan.acre"), 14, 20, -1,-1, -1,-1, 0,0, 1,0);
	return g;
}

bool tileSolid(gameData* gd, int x, int y)
{
	if (x < 0 || x >= gd->worldData.width || y < 0 && y >= gd->worldData.height) return false;
	if (gd->worldData.colBack[y * gd->worldData.width + x] == 1)
		return true;
	return false;
}

bool collision(gameData* gd, entity e, float newPlayerX, float newPlayerY)
{
	// no need to check startX, and startY, since the loop checks that one.
	if (tileSolid(gd, ((int)(newPlayerX + e.boundingBox.startX) / (int)TILE_W), ((int)(newPlayerY + e.boundingBox.endY)   / (int)TILE_W)) ||
		tileSolid(gd, ((int)(newPlayerX + e.boundingBox.endX)   / (int)TILE_W), ((int)(newPlayerY + e.boundingBox.endY)   / (int)TILE_W)) ||
		tileSolid(gd, ((int)(newPlayerX + e.boundingBox.endX)   / (int)TILE_W), ((int)(newPlayerY + e.boundingBox.startY) / (int)TILE_W)))
		return true;

	for (int x = e.boundingBox.startX; x <= e.boundingBox.endX; x += TILE_W-1)
		for (int y = e.boundingBox.startY; y <= e.boundingBox.endY; y += TILE_W-1)
			if (tileSolid(gd, ((int)(newPlayerX + x) / (int)TILE_W), ((int)(newPlayerY + y) / (int)TILE_W)))
				return true;
	
		return false;
}

void entityCalculations(gameData* gd, entity* e)
{
	float newY = e->py + timePerSec(e->vy);
	if (!collision(gd, *e, e->px, newY))
		e->py = newY;

	float newX = e->px + timePerSec(e->vx);
	if (!collision(gd, *e, newX, e->py))
		e->px = newX;
}

int cmSpaceX(gameData* gd, float x)
{
	float nx = x - (int)gd->cameraX + (gd->cameraX < 0 ? 1 : 0);
	if (nx < 0 && nx < (int)nx) // if the value is in negative domain, then if there is any floating point numbers, add -1.
		return (int)nx - 1;
	return nx;
}
int cmSpaceY(gameData* gd, float y)
{
	float ny = y - (int)gd->cameraY + (gd->cameraY < 0 ? 1 : 0);
	if (ny < 0 && ny < (int)ny) // if the value is in negative domain, then if there is any floating point numbers, add -1.
		return (int)ny - 1;
	return ny;
}

void drawEntity(gameData* gd, entity* e, bool focused)
{
	if		(e->facing == Up    && e->faceOps[0]) e->cSpr = &(e->coords[0]);
	else if (e->facing == Left  && e->faceOps[1]) e->cSpr = &(e->coords[1]);
	else if (e->facing == Down  && e->faceOps[2]) e->cSpr = &(e->coords[2]);
	else if (e->facing == Right && e->faceOps[3]) e->cSpr = &(e->coords[3]);
	
	int x, y;
	if (!focused)
	{
		x = cmSpaceX(gd, e->px);
		y = cmSpaceY(gd, e->py);
	}
	else
	{
		int w = e->textureW;
		int h = e->textureH;

		x = (Width(Screen) / 2 - w / 2);
		y = (Height(Screen) / 2 - h / 2);
	}
	if (spaceCollide(ScreenSpace, e->boundingBox))
	{
		drawPartialArea(x, y, e->textures, e->cSpr->x * e->textureW, e->cSpr->y * e->textureH, (e->cSpr->x+1)*e->textureW, (e->cSpr->y+1)*e->textureH); // draw entity sprite

		for (int i = e->boundingBox.startX; i <= e->boundingBox.endX; i++) // shadow
		{
			int r = 0, g = 0, b = 0;
			Xterm(surface.colBack[(y + e->boundingBox.endY) * Width(Screen) + x + i], &r, &g, &b);
			sysDrawPoint(x + i, y + e->boundingBox.endY, surface, Default, Default, Color(clamp(r - 50, 0, 255), clamp(g - 50, 0, 255), clamp(b - 50, 0, 255)));
		}

		if (gd->showBox) // draw boundingBox
		{
			sysDrawRect(x + e->boundingBox.startX, y + e->boundingBox.startY, x + e->boundingBox.endX + 1, y + e->boundingBox.endY + 1, surface, Default, false, Default, Magenta);
			sysDrawPoint(cmSpaceX(gd, e->px), cmSpaceY(gd, e->py), surface, Default, Default, Yellow);
		}
	}
}

void gameCalculations(gameData* gd)
{
	// ~~~~~~~~~ Setting Defaults ~~~~~~~~~~~~

	defaultBackColor = Black;

	gd->mob.vx = 0;
	gd->mob.vy = 0;
	gd->player.vx = 0;
	gd->player.vy = 0;
	
	// ~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~

	if (key(W).held) gd->player.vy = -30, gd->player.facing = Up;
	if (key(S).held) gd->player.vy = 30, gd->player.facing = Down;
	if (key(A).held) gd->player.vx = -30, gd->player.facing = Left;
	if (key(D).held) gd->player.vx = 30, gd->player.facing = Right;
	
	if (key(Up).held) gd->mob.vy = -40, gd->mob.facing = Up;
	if (key(Down).held) gd->mob.vy = 40, gd->mob.facing = Down;
	if (key(Left).held) gd->mob.vx = -40, gd->mob.facing = Left;
	if (key(Right).held) gd->mob.vx = 40, gd->mob.facing = Right;

	if (key(Num2).pressed) gd->showBox = !gd->showBox;
	if (key(Num1).pressed) gd->showInventory = !gd->showInventory;
	
	// ~~~~~~~~~~~~~ Collision ~~~~~~~~~~~~~~~~~~~

	entityCalculations(gd, &gd->mob);
	entityCalculations(gd, &gd->player);

	// camera positioning
	gd->cameraX = ((gd->player.px + (gd->player.textureW / 2)) - Width(Screen) / 2);
	gd->cameraY = ((gd->player.py + (gd->player.textureH / 2)) - Height(Screen) / 2);

	// ~~~~~~~~~~~~~ Rendering ~~~~~~~~~~~~~~~~~~~
	
	sysDrawPartialArea(gd->cameraX < 0 ? gd->cameraX * -1 + 1 : 0, gd->cameraY < 0 ? gd->cameraY * -1 + 1 : 0, surface, gd->levelOne, clamp(gd->cameraX, 0, gd->levelOne.width), clamp(gd->cameraY, 0, gd->levelOne.height), clamp(gd->cameraX + 1 + Screen.width, 0, gd->levelOne.width), clamp(gd->cameraY + 1 + Screen.height, 0, gd->levelOne.height));
	
	drawEntity(gd, &gd->player, true);
	drawEntity(gd, &gd->mob, false);
	
	if (gd->showInventory)
		drawInventory(cmSpaceY(gd, gd->player.py), gd->items);
}

// before, 277
// after sprite sheet 308
// after deleting un-needed comments 272