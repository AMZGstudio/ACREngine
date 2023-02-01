#pragma once
#include "screen.h"

enum types {user, bullet};

#define NEW_ID 150

typedef struct entity {
	float vx, vy, px, py;
	short facing; // Up, Down, Left, Right
	bool faceOps[4];
	Point coords[4];
	Point* cSpr;

	unsigned int attr;
	int type;
	int id;
	int textureW, textureH;
	Area textures;
	Space boundingBox;
} entity;

typedef struct entityNode {
	entity e;
	struct entityNode* next;

} entityNode;

typedef struct entities {
	entityNode* head;
	int numEntities;
} entities;

#include "physics.h"

entities initalizeEntities()
{
	entities e;
	e.head = NULL;
	e.numEntities = 0;
	return e;
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

	for (int x = w - 1; x >= 0; x--)
		for (int y = h - 1; y >= 0; y--)
			if (ar.colBack[y * ar.width + x] != Default)
			{
				if (!p2HitX)
					p2HitX = true, s.endX = x;
				if (y > s.endY)
					s.endY = y;
			}
	return s;
}

entity* getEntity(entities en, int id)
{
	entityNode* selected = en.head;
	while (selected != NULL)
	{
		if (selected->e.id == id)
			return &(selected->e);
		selected = selected->next;
	}		
	return NULL;
}
//
//entity* createEntity(entities* en, int id, int type, int x, int y, Area textures, int textureW, int textureH, int fx, int fy, int bx, int by, int lx, int ly, int rx, int ry)
//{
//	en->numEntities++;
//	en->allEntities = realloc(en->allEntities, sizeof(entity) * en->numEntities);
//
//	entity* e = &(en->allEntities[en->numEntities - 1]);
//	e->id = id;
//	e->type = type;
//	e->attr = 0;
//	e->px = x, e->py = y;
//	e->vx = 0, e->vy = 0;
//	e->textureW = textureW;
//	e->textureH = textureH;
//	
//	e->faceOps[0] = ((bx + by) >= 0) ? true : false, e->faceOps[1] = ((lx + ly) >= 0) ? true : false, e->faceOps[2] = ((fx + fy) >= 0) ? true : false, e->faceOps[3] = ((rx + ry) >= 0) ? true : false;
//
//	e->boundingBox = calculateBoundingBox(textures, textureW, textureH);
//	e->textures = textures;
//	e->coords[0].x = bx, e->coords[0].y = by, e->coords[1].x = lx, e->coords[1].y = ly;
//	e->coords[2].x = fx, e->coords[2].y = fy, e->coords[3].x = rx, e->coords[3].y = ry;
//	e->facing = (e->faceOps[2] ? Down : (e->faceOps[0] ? Up : (e->faceOps[1] ? Left : (Right))));
//	return e;
//}
//
//entityNode* createEntityNode(entities* ae, int id, int type, int x, int y, Area textures, int textureW, int textureH, int fx, int fy, int bx, int by, int lx, int ly, int rx, int ry)
//{
//	//entityNode* en = malloc(sizeof(entityNode));
//
//	//ae->head = en->e.allEntities = realloc(en->e.allEntities, sizeof(entity) * en->numEntities);
//
//	//entity* e = &(en->allEntities[en->numEntities - 1]);
//	en->e.id = id;
//	en->e.type = type;
//	en->e.attr = 0;
//	en->e.px = x, en->e.py = y;
//	en->e.vx = 0, en->e.vy = 0;
//	en->e.textureW = textureW;
//	en->e.textureH = textureH;
//
//	en->e.faceOps[0] = ((bx + by) >= 0) ? true : false, en->e.faceOps[1] = ((lx + ly) >= 0) ? true : false, en->e.faceOps[2] = ((fx + fy) >= 0) ? true : false, en->e.faceOps[3] = ((rx + ry) >= 0) ? true : false;
//
//	en->e.boundingBox = calculateBoundingBox(textures, textureW, textureH);
//	en->e.textures = textures;
//	en->e.coords[0].x = bx, en->e.coords[0].y = by, en->e.coords[1].x = lx, en->e.coords[1].y = ly;
//	en->e.coords[2].x = fx, en->e.coords[2].y = fy, en->e.coords[3].x = rx, en->e.coords[3].y = ry;
//	en->e.facing = (en->e.faceOps[2] ? Down : (en->e.faceOps[0] ? Up : (en->e.faceOps[1] ? Left : (Right))));
//	en->next = NULL;
//
//	ae->numEntities++;
//
//	if (ae->head == NULL)
//	{
//		ae->head = en;
//		return;
//	}
//	entityNode* selected = ae->head;
//	while (selected->next)
//		selected = selected->next;
//	
//	selected->next = en;
//	
//	
//
//
//	return en;
//}
//
//void freeEntity(entityNode* en)
//{
//	deleteArea(&(en->e.textures));
//	en->next == NULL;
//	free(en);
//}
//void deleteEntity(entities* en, int id)
//{
//	// if the list is empty exit
//	if (en->head != NULL)
//	{
//		// if the frame to remove is the head (first in link)
//		if (en->head->e.id == id)
//		{
//			entityNode* nextFrame = en->head->next;
//			entityNode* headFrame = en->head;
//
//			freeEntity(en->head);
//			en->numEntities--;
//
//			en->head = nextFrame;
//			return;
//		}
//		// used to connect the previous link with the next link
//		entityNode* prev = en->head;
//		entityNode* current = en->head;
//
//		while (current)
//		{
//			if (current->e.id == id)
//			{
//				prev->next = current->next;
//
//				freeEntity(current);
//				en->numEntities--;
//				return;
//			}
//			prev = current;
//			current = current->next;
//		}
//	}
//
//	//bool startCopy = false;
//	//for (int i = 0; i < en->numEntities; i++)
//	//{
//	//	if (en->allEntities[i].id == id)
//	//	{
//	//		en->allEntities[i].px = 0;
//	//		en->allEntities[i].py = 0;
//	//		en->allEntities[i].vx = 0;
//	//		en->allEntities[i].vy = 0;
//	//		//deleteArea(&(en->allEntities[i].textures));
//	//		startCopy = true;
//	//	}
//	//	/*if (startCopy && i < en->numEntities-1)
//	//	{
//	//		en->allEntities[i] = en->allEntities[i + 1];
//	//		
//	//	}*/
//	//}
//	//en->allEntities = realloc(en->allEntities, sizeof(entity) * en->numEntities);
//}
//
void drawEntities(entities en, float cameraX, float cameraY, bool showBox)
{
	entityNode* selected = en.head;
	while (selected != NULL)
	{
		entity e = selected->e; 
		// possible errors can be caused by entity facing illegal direction
		if      (e.facing == Up) e.cSpr = &(e.coords[0]);
		else if (e.facing == Left) e.cSpr = &(e.coords[1]);
		else if (e.facing == Down) e.cSpr = &(e.coords[2]);
		else if (e.facing == Right) e.cSpr = &(e.coords[3]);

		if (!legalArea(e.textures))
		{
			int x = cmSpace(cameraX, e.px);
			int y = cmSpace(cameraY, e.py);

			if (spaceCollide(ScreenSpace, e.boundingBox))
			{
				drawPartialArea(x, y, e.textures, e.cSpr->x * e.textureW, e.cSpr->y * e.textureH, (e.cSpr->x + 1) * e.textureW, (e.cSpr->y + 1) * e.textureH); // draw entity sprite

				for (int i = e.boundingBox.startX; i <= e.boundingBox.endX; i++) // shadow
				{
					short r = 0, g = 0, b = 0;
					Xterm(surface.colBack[(y + e.boundingBox.endY) * Width(Screen) + x + i], &r, &g, &b);
					sysDrawPoint(x + i, y + e.boundingBox.endY, surface, Default, Default, Color(clamp(r - 50, 0, 255), clamp(g - 50, 0, 255), clamp(b - 50, 0, 255)));
				}

				if (showBox) // draw boundingBox
				{
					sysDrawRect(x + e.boundingBox.startX, y + e.boundingBox.startY, x + e.boundingBox.endX + 1, y + e.boundingBox.endY + 1, surface, Default, false, Default, Magenta);
					sysDrawPoint(cmSpace(cameraX, e.px), cmSpace(cameraY, e.py), surface, Default, Default, Yellow);
				}
			}
		}
		selected = selected->next;
	}
}
//
//void entitiesCalculations(entities* en, Area worldData, int tileW)
//{
//	entityNode* selected = en->head;
//	while (selected != NULL)
//	{
//		bool hit = false;
//		float newY = selected->e.py + timePerSec(selected->e.vy);
//		if (!collision(worldData, *en, &(selected->e), selected->e.boundingBox, tileW, selected->e.px, newY))
//			selected->e.py = newY;
//		else hit = true;
//
//		float newX = selected->e.px + timePerSec(selected->e.vx);
//		if (!collision(worldData, *en, &(selected->e), selected->e.boundingBox, tileW, newX, selected->e.py))
//			selected->e.px = newX;
//		else hit = true;
//
//		if (selected->e.type == user)
//			selected->e.vx = 0, selected->e.vy = 0; // reset vx, and vy, for next loop
//
//		else if (selected->e.type == bullet && hit)
//		{
//			deleteEntity(en, selected->e.id);
//			//en->numEntities--;
//		}
//		selected = selected->next;
//	}
//}

int setFacing(int facing, entity* e)
{
	if (facing == Up && e->faceOps[0]) return (e->facing = Up);
	if (facing == Down && e->faceOps[2]) return (e->facing = Down);
	if (facing == Left && e->faceOps[1]) return (e->facing = Left);
	if (facing == Right && e->faceOps[3]) return (e->facing = Right);
}