#pragma once
#include "inventory.h"
#include "screen.h"
#include "entites.h"

#define TILE_W 14

enum characters {player, mob};

typedef struct gameData {
	float cameraX, cameraY;
	Area levelOne;
	Area worldData;
	Items items;

	entities e;
	bool showBox, showInventory, showNumEntities;
	
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

gameData initalizeGame()
{
	gameData g;
	defaultBackColor = Black;
	g.cameraX = 0, g.cameraY = 0;
	g.showBox = !1, g.showInventory = !1, g.showNumEntities = !1;

	g.worldData = loadSprite("../Levels/levelOne.acre");
	g.levelOne = loadLevel(g.worldData);

	g.e = initalizeEntities();
	g.items = initalizeInventory(10, 8);


	//createEntityNode(&g.e, player, user, 160, 160, loadSprite("../Sprites/bot.acre"), 12, 13, 1,0, 0,0, 0,1, 1,1);
	//createEntityNode(&g.e, mob, user, 180, 180, loadSprite("../Sprites/oldMan.acre"), 14, 20, -1,-1, -1,-1, 0,0, 1,0);
	return g;
}

void gameCalculations(gameData* gd)
{
	entity* p = getEntity(gd->e, player);
	entity* m = getEntity(gd->e, mob);

	// ~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~
	if (key(W).held) p->vy = -30, setFacing(Up, p);
	if (key(S).held) p->vy = 30, setFacing(Down, p);
	if (key(A).held) p->vx = -30, setFacing(Left, p);
	if (key(D).held) p->vx = 30, setFacing(Right, p);
	
	if (key(Up).held) m->vy = -40,   setFacing(Up, m);
	if (key(Down).held) m->vy = 40,  setFacing(Down, m); 
	if (key(Left).held) m->vx = -40, setFacing(Left, m);
	if (key(Right).held) m->vx = 40, setFacing(Right, m);

	if (key(Num2).pressed) gd->showBox = !gd->showBox;
	if (key(Num1).pressed) gd->showInventory = !gd->showInventory;
	if (key(Num3).pressed) gd->showNumEntities = !gd->showNumEntities;
	
	if (key(E).pressed)
	{
		entity* p = getEntity(gd->e, player);
		int x = p->px+p->textureW/2, y = p->py+p->textureH/2;

		//createEntityNode(&gd->e)
		//entity* b = createEntityNode(&gd->e, gd->e.numEntities, bullet, x,y, loadSprite("../Sprites/pointer.acre"), 7, 7, 0, 0, 0, 0, 0, 0, 0, 0);

		//if (p->vx < 0.5 && p->vx > -0.5)
		//{
		//	if (p->facing == Left) b->vx = -50;
		//	if (p->facing == Right) b->vx = +50;
		//}
		//else
		//	b->vx = p->vx + ((p->vx < 0) ? -20 : 20);

		//if (p->vy < 0.5 && p->vy > -0.5)
		//{
		//	if (p->facing == Up) b->vy = -50;
		//	if (p->facing == Down) b->vy = +50;
		//}
		//else	
		//	b->vy = p->vy + ((p->vy < 0) ? -20 : 20);
	}
	
	// ~~~~~~~~~~~~~ Entity Code ~~~~~~~~~~~~~~~~~~~

	//entitiesCalculations(&(gd->e), gd->worldData, TILE_W);

	// camera positioning
	gd->cameraX = ((p->px + (p->textureW / 2)) - Width(Screen) / 2);
	gd->cameraY = ((p->py + (p->textureH / 2)) - Height(Screen) / 2);

	// ~~~~~~~~~~~~~ Rendering ~~~~~~~~~~~~~~~~~~~
	sysDrawPartialArea(gd->cameraX < 0 ? gd->cameraX * -1 + 1 : 0, gd->cameraY < 0 ? gd->cameraY * -1 + 1 : 0, surface, gd->levelOne, clamp(gd->cameraX, 0, gd->levelOne.width), clamp(gd->cameraY, 0, gd->levelOne.height), clamp(gd->cameraX + 1 + Screen.width, 0, gd->levelOne.width), clamp(gd->cameraY + 1 + Screen.height, 0, gd->levelOne.height));
	drawEntities(gd->e, gd->cameraX, gd->cameraY, gd->showBox);

	if (gd->showInventory)
		drawInventory(cmSpace(gd->cameraY, p->py), gd->items);

	if (gd->showNumEntities)
		drawNumber(Centered, 0, gd->e.numEntities, Pzim, LightBlue);
}

// before, 277
// after sprite sheet 308
// after deleting un-needed comments 272
// after 266
// after 250
// 193
// 120
// 111

/*

	else
	{
		int w = e->textureW;
		int h = e->textureH;

		x = (Width(Screen) / 2 - w / 2);
		y = (Height(Screen) / 2 - h / 2);
	}
	
*/