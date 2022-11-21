#pragma once

#ifdef ACRE_3_COMPATIBLE
	#ifndef TRANSFORM_INCLUDES
		#define TRANSFORM_INCLUDES
		typedef struct AreaTrans {
			Area area;
			float x;
			float y;
			float zoom;
			float spy;
			float spx;
			float szx;
			float szy;
		} AreaTrans;
		AreaTrans createAreaTrans(Area areaData);
		void drawAreaTransformed(AreaTrans area, Area areaToDrawOn);
		void areaCalculations(AreaTrans* area);
		void flipArea(Area ar);

	#endif
#ifdef ACRE_TRANSFORM
AreaTrans createAreaTrans(Area areaData)
{
	AreaTrans a;
	a.area = areaData;
	a.x = -1;
	a.y = -1;
	a.zoom = 1;
	a.spx = 0;
	a.spy = 0;
	a.szx = 0;
	a.szy = 0;
	return a;
}

void drawAreaTransformed(AreaTrans area, Area areaToDrawOn)
{
	for(int y = 0; y < area.area.height; y++)
		for (int x = 0; x < area.area.width; x++)
		{
			int newX = clamp(area.x + (x * area.zoom), 0, Width(areaToDrawOn));
			int newY = clamp(area.y + (y * area.zoom), 0, Height(areaToDrawOn));
			int newXEnd = clamp(area.x + ((x + 1) * area.zoom), 0, Width(areaToDrawOn));
			int newYEnd = clamp(area.y + ((y + 1) * area.zoom), 0, Height(areaToDrawOn));
			
			Space s = { newX, newY, newXEnd, newYEnd };
			Space areaToDrawOnSpace = { 0, 0, areaToDrawOn.width, areaToDrawOn.height };

			if (spaceCollide(areaToDrawOnSpace, s))
				sysDrawRect(newX, newY, newXEnd, newYEnd, areaToDrawOn, Default, true, Default, area.area.colBack[y * area.area.width + x]);
		}
}

void areaCalculations(AreaTrans* area)
{
	Key keyState = key(LeftM);

	if (keyState.pressed)
		area->spx = Mouse.x, area->spy = Mouse.y;
	
	if (keyState.held)
	{
		area->x += (Mouse.x - area->spx);
		area->y += (Mouse.y - area->spy);
		area->spx = Mouse.x, area->spy = Mouse.y;
	}
	
	if (Mouse.scrollH < 0 || Mouse.scrollH > 0)
	{
		area->szx = ((Mouse.x - area->x) / area->zoom );
		area->szy = ((Mouse.y - area->y) / area->zoom);
		area->zoom *= Mouse.scrollH > 0 ? 1.05 : 0.95;

		float difX = (area->szx - ((Mouse.x - area->x) / area->zoom)) * area->zoom;
		float difY = (area->szy - ((Mouse.y - area->y) / area->zoom)) * area->zoom;
		area->x -= difX;
		area->y -= difY;
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

