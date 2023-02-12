#pragma once

#ifdef ACRE_3_COMPATIBLE
	#ifndef ACRE_EX_TRANSFORM
		#define ACRE_EX_TRANSFORM
	#endif
	
	#ifndef TRANSFORM_INCLUDES
		#define TRANSFORM_INCLUDES
		typedef struct AreaTrans {
			Area area;
			float zoom;
			float opacity; // between 0-1
			float x, y;
			float spy, spx;

			bool worldSpacePivot;
			bool allowDownscaleZoom;
			float xPivot, yPivot;
			Key oldStateLeftM;
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

	#endif
#ifdef ACRE_TRANSFORM
		
AreaTrans createAT(Area areaData, float x, float y)
{
	Space as = calcSpace(ScreenSpace, (int)x, (int)y, areaData.width, areaData.height);

	AreaTrans a;
	a.x = (float)as.startX;
	a.y = (float)as.startY;
	a.opacity = 1;

	a.area = areaData;
	a.spx = 0, a.spy = 0;

	a.zoom = 1;
	a.xPivot = (float)areaData.width / 2;
	a.yPivot = (float)areaData.width / 2;
	a.worldSpacePivot = false;

	a.allowDownscaleZoom = false;
	a.oldStateLeftM = key(LeftM);
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
			// this is a space, for the square that is created after zooming
			// the reason we do it this way, is that when using opacity, we have to draw
			// and calculate each pixel on the bigger square.
			Space shape;

			if (at->zoom == 1) // if there is no zoom, then it is 1 wide
			{
				shape.startX = x, shape.endX = x + 1;
				shape.startY = y, shape.endY = y + 1;
			}

			else // otherwise the size will be dependent on the zoom
			{
				shape.startX = (int)(x * at->zoom);
				shape.startY = (int)(y * at->zoom);
				shape.endX = (int)((x + 1) * at->zoom);
				shape.endY = (int)((y + 1) * at->zoom);
			}

			// create another space, but this one adjusts for actual screen space
			Space other = { shape.startX + (int)at->x, shape.startY + (int)at->y, shape.endX + (int)at->x, shape.endY + (int)at->y };

			// only draw this space if it collides (is on) with the screen space.
			if (spaceCollide(areaToDrawOnSpace, other))
			{
				// even if it collides it is then clamped to not be any bigger than necessary.
				shape.startX = (int)(clamp((float)shape.startX + at->x, 0, (float)area.width) - at->x);
				shape.startY = (int)(clamp((float)shape.startY + at->y, 0, (float)area.height) - at->y);
				shape.endX = (int)(clamp((float)shape.endX + at->x, 0, (float)area.width) - at->x);
				shape.endY = (int)(clamp((float)shape.endY + at->y, 0, (float)area.height) - at->y);

				for (int x2 = shape.startX; x2 < shape.endX; x2++)
					for (int y2 = shape.startY; y2 < shape.endY; y2++)
					{
						// if this pixel square is not on the screen, continue
						if (x2 + at->x > area.width || x2 + at->x < 0)
							continue;
						if (y2 + at->y > area.height || y2 + at->y < 0)
							continue;

						int area_i = y * at->area.width + x;

						// note the at-x < 0 ? 1:0 part is because when x & y are in the negative domain, integers get
						// rounded weirdly, and therefore this corrects them. (fixes camera glitches)
						int xUse = (int)at->x + (int)x2 - (at->x < 0 ? 1 : 0);
						int yUse = (int)at->y + (int)y2 - (at->y < 0 ? 1 : 0);

						int screen_i = (yUse) * (Screen.width) + (xUse);

						short color = calculateColor(at->area.colBack[area_i], area.colBack[screen_i], at->opacity);

						// finally draw each point in the square.
						sysDrawPoint((int)at->x + x2, (int)at->y + y2, area,
							at->area.drawText ? at->area.characters[area_i] : Default,
							at->area.drawFront ? at->area.colFront[area_i] : Default,
							at->area.drawBack ? color : Default
						);
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
	
	Key keyState = key(LeftM);

	if (keyState.held && !at->oldStateLeftM.held)
		at->spx = (float)Mouse.x, at->spy = (float)Mouse.y;
	
	if (keyState.held)
	{
		at->x += (Mouse.x - at->spx);
		at->y += (Mouse.y - at->spy);
		at->spx = (float)Mouse.x, at->spy = (float)Mouse.y;
	}
	
	if (Mouse.scrollH < 0 || Mouse.scrollH > 0)
	{
		sysChangeZoomAT(at, Mouse.scrollH > 0 ? 1.05f : 0.95f, true);
		/*if (!at->allowDownscaleZoom)
			if (at->zoom < 1)
			{
				at->zoom = 1;
				
			}*/

	}
	
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

