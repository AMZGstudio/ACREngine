#pragma once
#ifdef ACRE_3_COMPATIBLE
#ifdef ACRE_GUI

enum OptionStates {Button, Slider, TextBox};

typedef struct Window Window;

typedef struct Option {
	unsigned int type;
	bool bPressed;

	int xStart, yStart, xEnd, yEnd;
	char title[40];

	Window* windowBelongTo;
	bool oldLeftMState;
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

void addOption(Option* op, Window* wn)
{
	wn->numOps++;
	wn->ops = (Option**)realloc(wn->ops, sizeof(Option*) * wn->numOps);
	wn->ops[wn->numOps - 1] = op;
}

/*-------------------------------------------*\
|		Creating GUI Element Functions	   	  |
\*-------------------------------------------*/

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

Option* createOption()
{
	Option* op = (Option*)malloc(sizeof(Option));
	op->windowBelongTo = NULL;

	for (int i = 0; i < 40; i++)
		op->title[i] = 0;

	op->xStart = 0, op->yStart = 0, op->xEnd = 0, op->yEnd = 0;
	op->type = NULL;
	op->bPressed = false;
	op->oldLeftMState = false;
	return op;
}
Option* createButton(Window* parentWindow, int xStart, int yStart, int xEnd, int yEnd, const char* title)
{
	Space windowSpace = { parentWindow->x, parentWindow->y, parentWindow->x + parentWindow->width, parentWindow->y + parentWindow->height };
	Option* op = createOption();

	op->xStart = xStart == Centered ? ((parentWindow != NULL) ? center(xEnd, windowSpace, X) : center(xEnd, ScreenSpace, X)) : xStart;
	op->yStart = yStart == Centered ? ((parentWindow != NULL) ? center(yEnd, windowSpace, Y) : center(yEnd, ScreenSpace, Y)) : yStart;
	
	op->xEnd = xStart == Centered ? op->xStart + xEnd : xEnd;
	op->yEnd = yStart == Centered ? op->yStart + yEnd : yEnd;

	op->bPressed = false;
	op->type = Button;

	strcpy(op->title, title);

	if (parentWindow != NULL)
	{
		addOption(op, parentWindow);
		op->windowBelongTo = parentWindow;
	}
	return op;
}

//Option* createTextBox(Window* parentWindow)
//{
//
//}

//Option* createSlider(Window* parentWindow)
//{
//	
//}

/*-------------------------------------------*\
|		Calculating GUI Element Functions  	  |
\*-------------------------------------------*/

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

	Key keyState = key(LeftM);
	if (pointSpaceCollide(Mouse.x, Mouse.y, finalSpace))
	{
		if (keyState.held && (!button->oldLeftMState || button->bPressed))
			button->bPressed = true;

		else button->bPressed = false;
	}
	else
		button->bPressed = false;
	
	button->oldLeftMState = keyState.held;
	return button->bPressed;
}

/*-------------------------------------------*\
|		 Drawing GUI Element Functions  	  |
\*-------------------------------------------*/

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
		buttonSpace = spDrawRectFilled(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUTTON_PRESSED_COL : LIGHT_BUTTON_PRESSED_COL);
	else
		buttonSpace = spDrawRectFilled(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUTTON_COLOR : LIGHT_BUTTON_COLOR);

	spDrawText(Centered, Centered, buttonSpace, button->title, DefaultFont, White);
	
	return buttonSpace;
}

#endif
#else
#error You need to use a ACRE 3.0 Compatible version
#endif