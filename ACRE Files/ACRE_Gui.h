#pragma once
#ifdef ACRE_3_COMPATIBLE

#ifdef ACRE_GUI

#define BUTTON 1
#define SLIDER 2

enum OptionStates {Button, Slider, TextBox};

typedef struct Window Window;

typedef struct Option {
	unsigned int type;
	bool bPressed;

	int xStart, yStart, xEnd, yEnd;
	char title[40];

	Window* windowBelongTo = NULL;
} Option;

typedef struct Window {
	int width, height;
	int x, y;
	char* name;

	bool beingHeld;
	bool resizeable;
	bool drawOptions;

	int heldOffset;
	Option** ops;
	int numOps;

} Window;

#define LIGHT_TITLE_COLOR White
#define LIGHT_BUTTON_COLOR Color(120, 120, 120)
#define LIGHT_BUTTON_PRESSED_COL Color(100, 100, 100)
#define LIGHT_WINDOW_COL Color(180, 180, 180)

#define DARK_TITLE_COLOR Color(100, 100, 100)
#define DARK_BUTTON_COLOR DARK_TITLE_COLOR
#define DARK_BUTTON_PRESSED_COL Color(40, 40, 40)
#define DARK_WINDOW_COL DarkGrey

Window* createWindow(const int x, const int y, const int width, const int height, const char* name, bool resizeable)
{
	Window* window = (Window*)malloc(sizeof(Window));

	window->width = width;
	window->height = height;
	window->x = x;
	window->y = y;
	window->beingHeld = false;
	window->resizeable = resizeable;
	window->drawOptions = true;

	window->ops = NULL;
	window->numOps = 0;

	if (name != NULL)
	{
		window->name = (char*)malloc(sizeof(char) * 100);
		strcpy(window->name, name);
	}
	else
		window->name = NULL;
	
	return window;
}

void addOption(Option* op, Window* wn)
{
	wn->numOps++;
	wn->ops = (Option**)realloc(wn->ops, sizeof(Option*) * wn->numOps);
	wn->ops[wn->numOps - 1] = op;
}

Option* createSlider(Window* parentWindow)
{

}

Option* createButton(Window* parentWindow, int xStart, int yStart, int xEnd, int yEnd, const char* title)
{
	Option* op = (Option*)malloc(sizeof(Option));

	op->xStart = xStart;
	op->yStart = yStart;
	op->xEnd = xEnd;
	op->yEnd = yEnd;
	op->bPressed = false;
	op->type = Button;
	op->windowBelongTo = NULL;
	strcpy(op->title, title);

	if (parentWindow != NULL)
	{
		addOption(op, parentWindow);
		op->windowBelongTo = parentWindow;
	}
	return op;
}

Option* createTextBox(Window* parentWindow)
{

}

bool calculateWindow(Window* window)
{
	bool returnVal = false;
	bool leftMHeld = key(LeftM).held;

	if (Mouse.x >= window->x && Mouse.x <= window->x + window->width && Mouse.y >= window->y && Mouse.y <= window->y + window->height)
	{
		returnVal = true;
		if (Mouse.y == window->y)
		{
			if (leftMHeld)
			{
				if (window->beingHeld == false)
					window->heldOffset = window->x - Mouse.x;

				window->beingHeld = true;
			}
			else window->beingHeld = false;
		}
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
		returnVal = true;
	}
	return returnVal;
}

bool calculateButton(Option* button)
{
	Space finalSpace = { button->windowBelongTo->x + button->xStart, 
						 button->windowBelongTo->y + button->yStart, 
						 button->windowBelongTo->x + button->xEnd, 
						 button->windowBelongTo->y + button->yEnd };
	
	if (pointSpaceCollide(Mouse.x, Mouse.y, finalSpace) && key(LeftM).held)
	{
		button->bPressed = true;
	}
	else
		button->bPressed = false;
	return button->bPressed;
}

Space drawWindow(Window* window, bool dark)
{
	Space windowSpace = drawRectFilled(window->x, window->y, window->x+window->width, window->y+window->height, dark?DARK_WINDOW_COL:LIGHT_WINDOW_COL);
	
	for (int x = windowSpace.startX; x < windowSpace.endX; x++)
		drawPixel(x, windowSpace.startY, dark?DARK_TITLE_COLOR:LIGHT_TITLE_COLOR);

	if(window->name != NULL)
		sysDrawText(windowSpace.startX + 1, windowSpace.startY, Screen, window->name, DefaultFont, dark?White:Black, Default);
	
	return windowSpace;
}

Space drawButton(Option* button, bool dark)
{
	Space windowSpace = { button->windowBelongTo->x, button->windowBelongTo->y,
						  button->windowBelongTo->x + button->windowBelongTo->width,
						  button->windowBelongTo->y + button->windowBelongTo->height };

	Space buttonSpace;// = spDrawRect(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUTTON_COLOR : LIGHT_BUTTON_COLOR);

	if (button->bPressed)
		buttonSpace = spDrawRect(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUTTON_PRESSED_COL : LIGHT_BUTTON_PRESSED_COL);
	else
		buttonSpace = spDrawRect(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUTTON_COLOR : LIGHT_BUTTON_COLOR);

	spDrawText(Centered, Centered, buttonSpace, button->title, DefaultFont, White);
	
	return buttonSpace;
}




//Space getWindowSpace(Window* win)
//{
//	Space window = { win->x, win->y, win->x + win->width, win->y + win->height };
//	return window;
//}
//
//bool drawButton(Window* win, int xStart, int yStart, int xEnd, int yEnd, char* title, bool dark)
//{
//	Space windowSpace = { win->x, win->y, win->x + win->width, win->y + win->height };
//
//	bool returnVal = false;
//	Space button = sysDrawRect(xStart, yStart, xEnd, yEnd, windowSpace, Default, true, Default, dark?DARK_BUTTON_COLOR:LIGHT_BUTTON_COLOR);
//	sysDrawText(Centered, Centered, button, title, Default, White, Default);
//
//	if (pointSpaceCollide(Mouse.x, Mouse.y, button))
//	{
//		if (key(LeftM).held)
//		{
//			sysDrawRect(0, 0, Width(button), Height(button), button, Default, true, Default, dark?DARK_BUTTON_PRESSED_COL:LIGHT_BUTTON_PRESSED_COL);
//			returnVal = true;
//		}
//	}
//	return returnVal;
//}
//void drawButton(Space space, int x, int y, char* title, Font fontType)
//{
//	int borderW = 2;
//	int w = stringWidth(title, fontType)+borderW*2, h = 7 + borderW * 2;
//
//	Space s = getSpace(space, x, y, x == Centered ? w : x + w, y == Centered ? y : y + h);
//
//	bool drawn = false;
//	if (pointSpaceCollide(Mouse.x, Mouse.y, s))
//		if (key(LeftM).held)
//		{
//			drawn = true;
//			sysDrawRect(s.startX, s.startY, s.endX, s.endY, Screen, Default, true, Default, VeryDarkGrey);
//		}
//	
//	if (!drawn) sysDrawRect(s.startX, s.startY, s.endX, s.endY, Screen, Default, true, Default, Color(100,100,100));
//
//	sysDrawText(s.startX + borderW, s.startY + borderW-1, Screen, title, fontType, Default, White);
//	//sysDrawRect(s.startX, s.startY, s.endX, s.endY, Screen, Default, false, Default, VeryDarkGrey);
//}

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
#endif
#else
#error You need to use a ACRE 3.0 Compatible version
#endif