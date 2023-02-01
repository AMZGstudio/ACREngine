#include "screen.h"

bool tileSolid(Area worldData, int x, int y)
{
	//if (x < 0 || x >= gd->worldData.width || y < 0 && y >= gd->worldData.height) return false;
	if (worldData.colBack[y * worldData.width + x] == 1)
		return true;
	return false;
}

bool collision(Area worldData, entities en, entity* e, Space boundingBox, int tileW, float ex, float ey)
{
	// no need to check startX, and startY, since the loop checks that one.
	if (tileSolid(worldData, ((int)(ex + boundingBox.startX) / (int)tileW), ((int)(ey + boundingBox.endY) / (int)tileW)) ||
		tileSolid(worldData, ((int)(ex + boundingBox.endX) / (int)tileW), ((int)(ey + boundingBox.endY) / (int)tileW)) ||
		tileSolid(worldData, ((int)(ex + boundingBox.endX) / (int)tileW), ((int)(ey + boundingBox.startY) / (int)tileW)))
		return true;

	for (int x = boundingBox.startX; x <= boundingBox.endX; x += tileW - 1)
		for (int y = boundingBox.startY; y <= boundingBox.endY; y += tileW - 1)
			if (tileSolid(worldData, ((int)(ex + x) / (int)tileW), ((int)(ey + y) / (int)tileW)))
				return true;

	if (e != NULL && e->type != bullet)
	{
		entityNode* e2 = en.head; // current selected entity
		while (e2 != NULL)
		{
			if (!(e->id == e2->e.id) && !(e2->e.type == bullet))
			{
				int x1s = ex + e->boundingBox.startX, y1s = ey + e->boundingBox.startY;
				int x1e = ex + e->boundingBox.endX, y1e = ey + e->boundingBox.endY;

				int x2s = e2->e.px + e2->e.boundingBox.startX, y2s = e2->e.py + e2->e.boundingBox.startY;
				int x2e = e2->e.px + e2->e.boundingBox.endX, y2e = e2->e.py + e2->e.boundingBox.endY;

				if (rectangleCollide(x1s, y1s, x1e, y1e, x2s, y2s, x2e, y2e))
					return true;
			}
			e2 = e2->next;
		}
	}
		
	return false;
}