#pragma once

#ifdef ACRE_3_COMPATIBLE
	#ifndef TRANSFORM_INCLUDES
		#define TRANSFORM_INCLUDES
		typedef struct AreaTrans {
			Area area;
			float zoom;
			float x, y;
			float spy, spx;
			float szx, szy;
			Key oldStateLeftM;
		} AreaTrans;

		AreaTrans createAT(Area areaData, int x, int y);

		void sysDrawAT(AreaTrans at, Area area);
		void drawAT(AreaTrans at);

		void calculateAT(AreaTrans* at);
		void flipArea(Area ar);

	#endif
#ifdef ACRE_TRANSFORM
		
AreaTrans createAT(Area areaData, int x, int y)
{
	AreaTrans a;
	a.zoom = 1;
	a.area = areaData;
	a.x = (float)x, a.y = (float)y;
	a.spx = 0, a.spy = 0;
	a.szx = 0, a.szy = 0;
	a.oldStateLeftM = key(LeftM);
	return a;
}

void sysDrawAT(AreaTrans at, Area area)
{
	for (int y = 0; y < at.area.height; y++)
		for (int x = 0; x < at.area.width; x++)
		{
			int newX = clamp(at.x + (x * at.zoom), 0, Width(area));
			int newY = clamp(at.y + (y * at.zoom), 0, Height(area));
			int newXEnd = clamp(at.x + ((x + 1) * at.zoom), 0, Width(area));
			int newYEnd = clamp(at.y + ((y + 1) * at.zoom), 0, Height(area));

			Space s = { newX, newY, newXEnd, newYEnd };
			Space areaToDrawOnSpace = { 0, 0, area.width, area.height };

			if (spaceCollide(areaToDrawOnSpace, s))
				sysDrawRect(newX, newY, newXEnd, newYEnd, area, Default, true, Default, at.area.colBack[y * at.area.width + x]);
		}
}

void drawAT(AreaTrans at)
{
	sysDrawAT(at, *areaToDrawOn);
}

void changeZoom(AreaTrans* at, float xPivot, float yPivot, float zoomLevel, bool mulOrSet)
{
	at->szx = ((xPivot - at->x) / at->zoom);
	at->szy = ((yPivot - at->y) / at->zoom);

	at->szx = ((xPivot - at->x) / at->zoom);
	at->szy = ((yPivot - at->y) / at->zoom);

	at->zoom = mulOrSet ? at->zoom * zoomLevel : zoomLevel;

	float difX = (at->szx - ((xPivot - at->x) / at->zoom)) * at->zoom;
	float difY = (at->szy - ((yPivot - at->y) / at->zoom)) * at->zoom;
	at->x -= difX;
	at->y -= difY;
}

void calculateAT(AreaTrans* at)
{
	Key keyState = key(LeftM);

	if (keyState.held && !at->oldStateLeftM.held)
		at->spx = Mouse.x, at->spy = Mouse.y;
	
	if (keyState.held)
	{
		at->x += (Mouse.x - at->spx);
		at->y += (Mouse.y - at->spy);
		at->spx = Mouse.x, at->spy = Mouse.y;
	}
	
	if (Mouse.scrollH < 0 || Mouse.scrollH > 0)
		changeZoom(at, Mouse.x, Mouse.y, Mouse.scrollH > 0 ? 1.05f : 0.95f, true);
	
	at->oldStateLeftM = key(LeftM);
}

void flipArea(Area ar)
{
	for(int y = 0; y<ar.height; y++)
		for (int x = 0; x < ar.width/2; x++)
		{
			short sideOne = ar.colBack[y * ar.width + x];
			short sideTwo = ar.colBack[y * ar.width + (ar.width-x-1)];
			
			ar.colBack[y * ar.width + x] = sideTwo;
			ar.colBack[y * ar.width + (ar.width - x - 1)] = sideOne;
		}
}

#endif
#else
#error You need to use a ACRE 3.0 Compatible version
#endif

