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
	a.x = x, a.y = y;
	a.spx = 0, a.spy = 0;
	a.szx = 0, a.szy = 0;
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

void calculateAT(AreaTrans* at)
{
	Key keyState = key(LeftM);

	if (keyState.pressed)
		at->spx = Mouse.x, at->spy = Mouse.y;
	
	if (keyState.held)
	{
		at->x += (Mouse.x - at->spx);
		at->y += (Mouse.y - at->spy);
		at->spx = Mouse.x, at->spy = Mouse.y;
	}
	
	if (Mouse.scrollH < 0 || Mouse.scrollH > 0)
	{
		at->szx = ((Mouse.x - at->x) / at->zoom );
		at->szy = ((Mouse.y - at->y) / at->zoom);
		at->zoom *= Mouse.scrollH > 0 ? 1.05 : 0.95;

		float difX = (at->szx - ((Mouse.x - at->x) / at->zoom)) * at->zoom;
		float difY = (at->szy - ((Mouse.y - at->y) / at->zoom)) * at->zoom;
		at->x -= difX;
		at->y -= difY;
	}
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

