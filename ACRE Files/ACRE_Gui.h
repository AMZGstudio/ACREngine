#pragma once
#ifdef ACRE_3_COMPATIBLE
#ifdef ACRE_GUI

enum OptionStates {Button, Slider, TextBox};
#define TEXT_SIZE 100

typedef struct Window Window;

typedef struct Option {
	unsigned int type;
	bool pressed;
	bool held;
	bool released;

	float sliderVal;
	int xStart, yStart, xEnd, yEnd;
	char title[TEXT_SIZE];

	Font font;
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
	bool outline;

	int heldOffsetX;
	int heldOffsetY;
	Option** ops;
	int numOps;

} Window;

#define LIGHT_WINDOW_COL Color(160, 160, 160)
#define LIGHT_BUT_ON_COL Color(100, 100, 100)
#define LIGHT_BUT_OF_COL Color(120, 120, 120)
#define LIGHT_SLIDEB_COL Color(80, 80, 80)
#define LIGHT_SLIDEF_COL Color(100, 100, 100)
#define LIGHT_TITLE_COL Color(100, 100, 100)
#define LIGHT_TEXT_COL Black

#define DARK_WINDOW_COL Color(70, 70, 70)
#define DARK_BUT_ON_COL Color(80, 80, 80)
#define DARK_BUT_OF_COL Color(105, 105, 105)
#define DARK_SLIDEB_COL Color(50, 50, 50)
#define DARK_SLIDEF_COL Color(100, 100, 100)
#define DARK_TITLE_COL Color(100, 100, 100)
#define DARK_TEXT_COl White

void addOption(Option* op, Window* wn)
{
	wn->numOps++;
	wn->ops = (Option**)realloc(wn->ops, sizeof(Option*) * wn->numOps);
	wn->ops[wn->numOps - 1] = op;
}

Space getWindowSpace(Window* wn)
{
	Space w = { 0,0,0,0 };
	if (wn != NULL)
	{
		w.startX = wn->x;
		w.startY = wn->y;
		w.endX = wn->x + wn->width;
		w.endY = wn->y + wn->height;
	}
	return w;
}

Space getWindowSpaceFull(Window* wn)
{
	Space w = getWindowSpace(wn);
	w.startY -= 3;
	return w;
}

/*-------------------------------------------*\
|		Creating GUI Element Functions	   	  |
\*-------------------------------------------*/

Window* createWindow(const int x, const int y, const int width, const int height, const char* name, bool resizeable)
{
	Window* window = (Window*)malloc(sizeof(Window));

	window->width = width;
	window->height = height;
	window->x = x == Centered ? (spWidth(ScreenSpace) / 2) - (width / 2) : x;
	window->y = (y == Centered ? (spHeight(ScreenSpace) / 2) - (height / 2): y) + 3;

	window->beingHeld = false;
	window->resizeable = resizeable;
	window->drawOptions = true;
	window->outline = true;

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

Option* createOption(Window* parentWindow)
{
	Option* op = (Option*)malloc(sizeof(Option));

	for (int i = 0; i < TEXT_SIZE; i++)
		op->title[i] = 0;

	op->xStart = 0, op->yStart = 0, op->xEnd = 0, op->yEnd = 0;
	op->type = NULL;
	op->pressed = false;
	op->held = false;
	op->oldLeftMState = false;
	op->font = DefaultFont;

	if (parentWindow != NULL)
	{
		addOption(op, parentWindow);
		op->windowBelongTo = parentWindow;
	}
	else
		op->windowBelongTo = NULL;

	return op;
}

Option* createButton(Window* parentWindow, int xStart, int yStart, int xEnd, int yEnd, const char* title)
{
	Space windowSpace = getWindowSpace(parentWindow);
	Option* op = createOption(parentWindow);

	op->xStart = xStart == Centered ? ((parentWindow != NULL) ? center(xEnd, windowSpace, X) : center(xEnd, ScreenSpace, X)) : xStart;
	op->yStart = yStart == Centered ? ((parentWindow != NULL) ? center(yEnd, windowSpace, Y) : center(yEnd, ScreenSpace, Y)) : yStart;
	
	op->xEnd = xStart == Centered ? op->xStart + xEnd : xEnd;
	op->yEnd = yStart == Centered ? op->yStart + yEnd : yEnd;

	op->type = Button;

	strcpy(op->title, title);
	
	return op;
}

Option* createTextBox(Window* parentWindow, int x, int y, const char* text, Font font)
{
	Space windowSpace = getWindowSpace(parentWindow);
	Option* op = createOption(parentWindow);

	op->xStart = x == Centered ? ((parentWindow != NULL) ? center(txtWidth(text, font), windowSpace, X) : center(txtWidth(text, font), ScreenSpace, X)) : x;
	op->yStart = y == Centered ? ((parentWindow != NULL) ? center(txtHeight(text, font), windowSpace, Y) : center(txtHeight(text, font), ScreenSpace, Y)) : y;

	op->xEnd = op->xStart + txtWidth(text, font);
	op->yEnd = op->yStart + txtHeight(text, font);

	op->font = font;
	op->type = TextBox;

	strcpy(op->title, text);
	return op;
}

Option* createSlider(Window* parentWindow, int xStart, int yStart, int xEnd, int yEnd, float slideStartLoc) // slide start loc is float between 0, and 100
{
	Space windowSpace = getWindowSpace(parentWindow);
	Option* op = createOption(parentWindow);

	op->xStart = xStart == Centered ? ((parentWindow != NULL) ? center(xEnd, windowSpace, X) : center(xEnd, ScreenSpace, X)) : xStart;
	op->yStart = yStart == Centered ? ((parentWindow != NULL) ? center(yEnd, windowSpace, Y) : center(yEnd, ScreenSpace, Y)) : yStart;

	op->xEnd = xStart == Centered ? op->xStart + xEnd : xEnd;
	op->yEnd = yStart == Centered ? op->yStart + yEnd : yEnd;

	op->type = Slider;
	op->sliderVal = clamp(slideStartLoc, 1, 100);
	return op;
}

/*-------------------------------------------*\
|		Calculating GUI Element Functions  	  |
\*-------------------------------------------*/

bool calculateWindow(Window* window)
{
	bool returnVal = false;
	bool leftMHeld = key(LeftM).held;

	Space titlebar = { window->x, window->y - 3, window->x + window->width, window->y };
	
	if ((pointSpaceCollide(Mouse.x, Mouse.y, titlebar) && leftMHeld) || (leftMHeld && window->beingHeld))
	{
		if (!window->beingHeld)
		{
			window->heldOffsetY = titlebar.startY - Mouse.y + 3;
			window->heldOffsetX = titlebar.startX - Mouse.x;

			window->beingHeld = true;
		}
	}
	else
	{
		window->beingHeld = false;
	}
	/*if (window->resizeable)
	{
		if (leftMHeld)
		{
			
		}
	}*/
	if (window->beingHeld)
	{
		window->x = Mouse.x + window->heldOffsetX;
		window->y = Mouse.y + window->heldOffsetY;
		returnVal = true;
	}
	return pointSpaceCollide(Mouse.x, Mouse.y, getWindowSpaceFull(window));
}

void calculateButton(Option* button)
{
	Space finalSpace = { button->windowBelongTo->x + button->xStart, 
						 button->windowBelongTo->y + button->yStart, 
						 button->windowBelongTo->x + button->xEnd, 
						 button->windowBelongTo->y + button->yEnd };

	//sysDrawRect(finalSpace.startX, finalSpace.startY, finalSpace.endX, finalSpace.endY, Screen, Default, false, Default, Red);
	Key keyState = key(LeftM);
	if (pointSpaceCollide(Mouse.x, Mouse.y, finalSpace))
	{
		if (keyState.held && (!button->oldLeftMState || button->held))
			button->held = true;

		else button->held = false;
	}
	else
		button->held = false;
	
	if (button->oldLeftMState == false && button->held)
		button->pressed = true;
	else button->pressed = false;

	button->oldLeftMState = keyState.held;
}

void calculateSlider(Option* slider)
{
	Space finalSpace = { slider->windowBelongTo->x + slider->xStart, 
						 slider->windowBelongTo->y + slider->yStart, 
						 slider->windowBelongTo->x + slider->xEnd, 
						 slider->windowBelongTo->y + slider->yEnd };

	slider->sliderVal = clamp(slider->sliderVal, 1, 100);

	if (pointSpaceCollide(Mouse.x, Mouse.y, finalSpace) && key(LeftM).held)
	{
		slider->sliderVal = map(Mouse.x, finalSpace.startX, finalSpace.endX, 1, 100);
	}
}

/*-------------------------------------------*\
|		 Drawing GUI Element Functions  	  |
\*-------------------------------------------*/

void drawShade(int xStart, int yStart, int xEnd, int yEnd)
{
	for (int y = yStart; y < yEnd; y++)
		for (int x = xStart; x < xEnd; x++)
		{
			short r, g, b;
			Xterm(getPointBack(x, y), &r, &g, &b);

			if (y == yStart || x == xStart)
				drawPixel(x, y, Color(r + 20, g + 20, b + 20));
			else if (y == yEnd - 1 || x == xEnd - 1)
				drawPixel(x, y, Color(r - 20, g - 20, b - 20));
		}
}

Space drawWindow(Window* window, bool dark)
{
	Space windowSpace = drawRectFilled(window->x, window->y, window->x+window->width, window->y+window->height, dark ? DARK_WINDOW_COL : LIGHT_WINDOW_COL);
	sysDrawRect(windowSpace.startX, windowSpace.startY-3, windowSpace.endX, windowSpace.startY, Screen, true, Default, Default, dark ? DARK_TITLE_COL : LIGHT_TITLE_COL);

	drawShade(windowSpace.startX, windowSpace.startY-3, windowSpace.endX, windowSpace.endY);

	if(window->name != NULL)
		sysDrawText(windowSpace.startX + 2, windowSpace.startY-2, Screen, window->name, DefaultFont, dark ? White : Black, Default);
	
	return windowSpace;
}

Space drawButton(Option* button, bool dark)
{
	Space windowSpace = getWindowSpace(button->windowBelongTo);
	Space buttonSpace;

	if (button->held) buttonSpace = spDrawRectFilled(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUT_ON_COL : LIGHT_BUT_ON_COL);
	else				  buttonSpace = spDrawRectFilled(button->xStart, button->yStart, button->xEnd, button->yEnd, windowSpace, dark ? DARK_BUT_OF_COL : LIGHT_BUT_OF_COL);
	
	drawShade(buttonSpace.startX, buttonSpace.startY, buttonSpace.endX, buttonSpace.endY);
	spDrawText(Centered, Centered, buttonSpace, button->title, DefaultFont, Black);
	
	return buttonSpace;
}

Space drawTextBox(Option* textbox, bool dark)
{
	Space windowSpace = getWindowSpace(textbox->windowBelongTo);
	return spDrawText(textbox->xStart, textbox->yStart, textbox->windowBelongTo == NULL ? ScreenSpace : windowSpace, textbox->title, textbox->font, dark ? DARK_TEXT_COl : LIGHT_TEXT_COL);
}

void drawSlider(Option* slider, bool dark)
{
	Space windowSpace = getWindowSpace(slider->windowBelongTo);
	
	spDrawRectFilled(slider->xStart, slider->yStart, slider->xEnd, slider->yEnd, windowSpace, dark ? DARK_SLIDEB_COL : LIGHT_SLIDEB_COL);
	int newX = map(slider->sliderVal, 1, 100, slider->xStart, slider->xEnd);
	
	spDrawRectFilled(newX, slider->yStart, newX + 1, slider->yEnd, windowSpace, dark ? DARK_SLIDEF_COL : LIGHT_SLIDEF_COL);
}

/*-------------------------------------------*\
|			  Delete Gui Elements			  |
\*-------------------------------------------*/

void deleteWindow(Window* wn)
{
	free(wn->ops);
}

#endif
#else
#error You need to use a ACRE 3.0 Compatible version
#endif