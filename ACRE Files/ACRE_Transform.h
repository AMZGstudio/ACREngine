#pragma once

#ifdef ACRE_31_COMPATIBLE
	#ifndef ACRE_EX_TRANSFORM
		#define ACRE_EX_TRANSFORM
	#endif
	
	typedef struct AreaTrans {
		Area area;
		float zoom;
		float opacity; // between 0-1
		float x, y;
		float spy, spx;

		bool worldSpacePivot;
		bool allowDownscaleZoom;
		float xPivot, yPivot;
	} AreaTrans;

	AreaTrans createAT(Area areaData, float x, float y);
	short calculateColor(short colorArea, short colorScreen, float opacity);

	void setPivotAT(AreaTrans* at, float xPivot, float yPivot, bool worldSpace);

	void sysDrawAT(AreaTrans* at, Area area);
	void sysChangeZoomAT(AreaTrans* at, float zoomLevel, bool mulOrSet);

	void drawAT(AreaTrans* at);
	void setZoomAT(AreaTrans* at, float zoom);
	void incZoomAT(AreaTrans* at, float zoom);
	void mulZoomAT(AreaTrans* at, float zoom);

	void calculateAT(AreaTrans* at);
	void flipArea(Area ar);

	
#ifdef ACRE_TRANSFORM
		
AreaTrans createAT(Area areaData, float x, float y)
{
	Space as = calcSpace(ScreenSpace, (int)x, (int)y, areaData.width, areaData.height);

	AreaTrans a;
	a.x = (float)as.xStart;
	a.y = (float)as.yStart;
	a.area = areaData;
	a.spx = 0, a.spy = 0;

	a.opacity = 1;
	a.zoom = 1;
	a.xPivot = (float)areaData.width / 2.0f;
	a.yPivot = (float)areaData.width / 2.0f;

	a.worldSpacePivot = false;
	a.allowDownscaleZoom = false;
	return a;
}

short calculateColor(short colorArea, short colorScreen, float opacity)
{
	if (opacity == 1)
		return colorArea;

	if (opacity == 0)
		return Default;

	if (colorArea == Default)
		return colorScreen;
	
	short tr, tg, tb; // t = this
	short br, bg, bb; // b = background

	Xterm(colorScreen, &br, &bg, &bb);
	Xterm(colorArea,   &tr, &tg, &tb);

	short r = (short)(tr * opacity + (1 - opacity) * br);
	short g = (short)(tg * opacity + (1 - opacity) * bg);
	short b = (short)(tb * opacity + (1 - opacity) * bb);

	return Color(r, g, b);
}

void setPivotAT(AreaTrans* at, float xPivot, float yPivot, bool worldSpace)
{
	at->worldSpacePivot = worldSpace;

	if (xPivot == Centered) at->xPivot = (float)at->area.width / 2.0f;
	else at->xPivot = xPivot;

	if (yPivot == Centered) at->yPivot = (float)at->area.height / 2.0f;
	else at->yPivot = yPivot;
}

void sysDrawAT(AreaTrans* at, Area area)
{
	if ((at->opacity = clamp(at->opacity, 0, 1)) == 0)
		return;

	Space areaToDrawOnSpace = { 0, 0, area.width, area.height };
	for (int y = 0; y < at->area.height; y++)
		for (int x = 0; x < at->area.width; x++)
		{
			// this is the rectangle for a single pixel, and it is adjusted to the world coordinates.
			// for now it just has the world coordinates, it will then be filled in further.
			Space shape = { at->x, at->y, at->x, at->y };

			// adust coordinates according to the x and y manipulated by the zoom.
			shape.xStart += (int)(x * at->zoom);
			shape.yStart += (int)(y * at->zoom);
			shape.xEnd += (int)((x + 1) * at->zoom);
			shape.yEnd += (int)((y + 1) * at->zoom);

			// only draw this space if it overlaps (is on) with the screen space.
			if (spaceOverlap(areaToDrawOnSpace, shape))
			{
				// even if it collides it is then clamped to not be any bigger than necessary.
				clampSpace(&shape, areaToDrawOnSpace);
			
				for (int y2 = shape.yStart; y2 < shape.yEnd; y2++)
					for (int x2 = shape.xStart; x2 < shape.xEnd; x2++)
					{
						int area_i = y * at->area.width + x;
						int screen_i = y2 * Screen.width + x2;

						short color = calculateColor(at->area.colBack[area_i], area.colBack[screen_i], at->opacity);

						// finally draw each point in the square.
						sysDrawPoint(x2, y2, area,
							at->area.drawText ? at->area.characters[area_i] : Default,
							at->area.drawFront ? at->area.colFront[area_i] : Default,
							at->area.drawBack ? color : Default );
					}
			}
		}
}

void sysChangeZoomAT(AreaTrans* at, float zoomLevel, bool mulOrSet)
{
	float realZoom = (mulOrSet ? at->zoom * zoomLevel : zoomLevel);
	
	// dont allow zooming in, greater than 100000
	if (realZoom > 10000)
		return;

	if (realZoom < 1 && !at->allowDownscaleZoom)
	{
		zoomLevel = 1;
		return;
	}

	// save the old pivot
	float xPiv = at->xPivot;
	float yPiv = at->yPivot;

	if (!at->worldSpacePivot)
		xPiv += at->x, yPiv += at->y;

	float szx = ((xPiv - at->x) / at->zoom);
	float szy = ((yPiv - at->y) / at->zoom);

	at->zoom = realZoom;

	float difX = (szx - ((xPiv - at->x) / at->zoom)) * at->zoom;
	float difY = (szy - ((yPiv - at->y) / at->zoom)) * at->zoom;

	at->x -= difX;
	at->y -= difY;

	return;
}

void drawAT(AreaTrans* at)
{
	sysDrawAT(at, *areaToDrawOn);
}

void setZoomAT(AreaTrans* at, float zoom)
{
	sysChangeZoomAT(at, zoom, false);
}

void incZoomAT(AreaTrans* at, float zoom)
{
	float currZoom = at->zoom;
	sysChangeZoomAT(at, at->zoom + zoom, false);
}

void mulZoomAT(AreaTrans* at, float zoom)
{
	sysChangeZoomAT(at, zoom, true);
}

void calculateAT(AreaTrans* at)
{
	setPivotAT(at, (float)Mouse.x, (float)Mouse.y, true);
	
	if (key(LMB).pressed)
		at->spx = (float)Mouse.x, at->spy = (float)Mouse.y;
	
	if (key(LMB).held)
	{
		at->x += (Mouse.x - at->spx);
		at->y += (Mouse.y - at->spy);
		at->spx = (float)Mouse.x, at->spy = (float)Mouse.y;
	}
	
	if (Mouse.scrollH != 0)
		sysChangeZoomAT(at, Mouse.scrollH > 0 ? 1.05f : 0.95f, true);
}

void flipArea(Area ar)
{
	for (int y = 0; y<ar.height; y++)
		for (int x = 0; x < ar.width / 2; x++)
		{
			short sideOne = ar.colBack[y * ar.width + x];
			short sideTwo = ar.colBack[y * ar.width + (ar.width-x-1)];
			
			ar.colBack[y * ar.width + x] = sideTwo;
			ar.colBack[y * ar.width + (ar.width - x - 1)] = sideOne;
		}
}

#endif
#else
#error You need to use an ACRE 3.1 compatible version
#endif