#include "ACREngine.h"

typedef struct Window {
	int width, height;
	int x, y;
	char* name;
	bool beingHeld;
	bool resizeable;
	int heldOffset;
} Window;

#define LIGHT_TITLE_COLOR White
#define LIGHT_BUTTON_COLOR Color(120, 120, 120)
#define LIGHT_BUTTON_PRESSED_COL Color(100, 100, 100)
#define LIGHT_WINDOW_COL Color(180, 180, 180)

#define DARK_TITLE_COLOR Color(100, 100, 100)
#define DARK_BUTTON_COLOR DARK_TITLE_COLOR
#define DARK_BUTTON_PRESSED_COL Color(40, 40, 40)
#define DARK_WINDOW_COL DarkGrey

Window* createWindow(int x, int y, int width, int height, char* name, bool resizeable)
{
	Window* window = (Window*)malloc(sizeof(Window));

	window->width = width;
	window->height = height;
	window->x = x;
	window->y = y;
	window->beingHeld = false;
	window->resizeable = resizeable;
	if (name != NULL)
	{
		window->name = malloc(sizeof(char) * 100);
		strcpy(window->name, name);
	}
	else
		window->name = NULL;
	
	return window;
}
void calculateWindow(Window* window)
{
	bool leftMHeld = key(LeftM).held;
	if (Mouse.x >= window->x && Mouse.x <= window->x + window->width && Mouse.y == window->y)
	{
		if (leftMHeld)
		{
			if(window->beingHeld == false)
				window->heldOffset = window->x - Mouse.x;

			window->beingHeld = true;
		}
		else window->beingHeld = false;
	}
	/*if (window->resizeable)
	{
		if (leftMHeld)
		{
			
		}
	}*/
	if (window->beingHeld)
	{
		window->x = Mouse.x + window->heldOffset;
		window->y = Mouse.y;
	}
}
Space drawWindow(Window* window, bool dark)
{
	Space windowSpace = drawRectFilled(window->x, window->y, window->x+window->width, window->y+window->height, dark?DARK_WINDOW_COL:LIGHT_WINDOW_COL);
	
	for (int x = windowSpace.startX; x < windowSpace.endX; x++)
		drawPoint(x, windowSpace.startY, dark?DARK_TITLE_COLOR:LIGHT_TITLE_COLOR);

	if(window->name != NULL)
	sysDrawText(windowSpace.startX + 1, windowSpace.startY, Screen, window->name, Default, dark?White:Black, Default);
	
	return windowSpace;
}
Space getWindowSpace(Window* win)
{
	Space window = { win->x, win->y, win->x + win->width, win->y + win->height };
	return window;
}

bool drawButton(Window* win, int xStart, int yStart, int xEnd, int yEnd, char* title, bool dark)
{
	Space windowSpace = { win->x, win->y, win->x + win->width, win->y + win->height };

	bool returnVal = false;
	Space button = sysDrawRect(xStart, yStart, xEnd, yEnd, windowSpace, Default, true, Default, dark?DARK_BUTTON_COLOR:LIGHT_BUTTON_COLOR);
	sysDrawText(Centered, Centered, button, title, Default, White, Default);

	if (pointSpaceCollide(Mouse.x, Mouse.y, button))
	{
		if (key(LeftM).held)
		{
			sysDrawRect(0, 0, Width(button), Height(button), button, Default, true, Default, dark?DARK_BUTTON_PRESSED_COL:LIGHT_BUTTON_PRESSED_COL);
			returnVal = true;
		}
	}
	return returnVal;
}

//Space sysDrawOutline(int xStart, int yStart, int xEnd, int yEnd, Space screenSpace, int colorFront, int colorBack)
	//{
	//	Space windowSpace = { 0,0,0,0 };
	//	if (xStart == Centered) windowSpace.startX = center(xEnd, screenSpace, X), windowSpace.endX = windowSpace.startX + xEnd - 1;
	//	else windowSpace.startX = xStart, windowSpace.endX = xEnd;

	//	if (yStart == Centered) windowSpace.startY = center(yEnd, screenSpace, Y), windowSpace.endY = windowSpace.startY + yEnd - 1;
	//	else windowSpace.startY = yStart, windowSpace.endY = yEnd;

	//	//draw it
	//	int tl = 218, tr = 191, bl = 192, br = 217, rl = 179, tb = 196;

	//	for (int x = windowSpace.startX; x <= windowSpace.endX; x++)
	//		for (int y = windowSpace.startY; y <= windowSpace.endY; y++)
	//		{
	//			//if we are in the first column or the last column.
	//			if (y == windowSpace.startY || y == windowSpace.endY)
	//			{
	//				if (y == windowSpace.startY && x == windowSpace.startX) sysDrawPoint(x, y, screenSpace, tl, colorFront, colorBack);
	//				else if (y == windowSpace.startY && x == windowSpace.endX) sysDrawPoint(x, y, screenSpace, tr, colorFront, colorBack);
	//				else if (y == windowSpace.endY && x == windowSpace.startX) sysDrawPoint(x, y, screenSpace, bl, colorFront, colorBack);
	//				else if (y == windowSpace.endY && x == windowSpace.endX) sysDrawPoint(x, y, screenSpace, br, colorFront, colorBack);
	//				else sysDrawPoint(x, y, screenSpace, tb, colorFront, colorBack);
	//			}
	//			else if (x == windowSpace.startX || x == windowSpace.endX)
	//				sysDrawPoint(x, y, screenSpace, rl, colorFront, colorBack);
	//		}
	//	return windowSpace;
	//}
//	Space drawOutline(int xStart, int yStart, int xEnd, int yEnd, int color){return sysDrawOutline(xStart, yStart, xEnd, yEnd, Screen, color, Default);}
