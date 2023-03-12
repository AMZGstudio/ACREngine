#pragma once

#ifdef ACRE_31_COMPATIBLE
	#define ACRE_EX_GUI

	#define TEXT_SIZE 100
	#define LIGHT_WINDOW_COL calcColor(160, 160, 160)
	#define LIGHT_BUT_ON_COL calcColor(100, 100, 100)
	#define LIGHT_BUT_OF_COL calcColor(120, 120, 120)
	#define LIGHT_SLIDEB_COL calcColor(80, 80, 80)
	#define LIGHT_SLIDEF_COL calcColor(100, 100, 100)
	#define LIGHT_TITLE_COL calcColor(100, 100, 100)
	#define LIGHT_TEXT_COL Black

	#define DARK_WINDOW_COL calcColor(70, 70, 70)
	#define DARK_BUT_ON_COL calcColor(80, 80, 80)
	#define DARK_BUT_OF_COL calcColor(105, 105, 105)
	#define DARK_SLIDEB_COL calcColor(50, 50, 50)
	#define DARK_SLIDEF_COL calcColor(100, 100, 100)
	#define DARK_TITLE_COL calcColor(100, 100, 100)
	#define DARK_TEXT_COl White

	enum OptionStates { Button, Slider, TextBox };
	typedef struct Window Window;

	typedef struct Option {
		unsigned int type;
		int x, y, width, height;
		bool beingHeld;
		bool wasPressed;

		float sliderVal;
		char title[TEXT_SIZE];

		Font font;
		Window* _window;

	} Option;

	typedef struct Window {
		int x, y, width, height;
		int heldOffsetX, heldOffsetY;

		bool beingHeld;
		Option** ops;
		char* name;
		int numOps;

	} Window;

	// delcarations go here
	Window* createWindow(const int x, const int y, const int width, const int height, const char* name);
	Option* createButton(Window* parentWindow, int x, int y, int width, int height, const char* title);
	Option* createTextBox(Window* parentWindow, int x, int y, const char* text, Font font);
	Option* createSlider(Window* parentWindow, int x, int y, int width, int height, float slideStartLoc);

	bool calculateWindow(Window* window);
	bool calculateButton(Option* button);
	bool calculateSlider(Option* slider);

	Space drawWindowAndContents(Window* w, bool dark);
	Space drawWindow(Window* window, bool dark);
	void drawOption(Option* op, bool dark);
	
#ifdef ACRE_GUI
#undef ACRE_GUI

	void _addOption(Option* op, Window* wn)
	{
		if (wn == NULL)
			return;

		wn->numOps++;
		wn->ops = (Option**)realloc(wn->ops, sizeof(Option*) * wn->numOps);
		wn->ops[wn->numOps - 1] = op;
	}

	Space _windowSpace(Window* wn)
	{
		Space w;
		w.xStart = wn->x;
		w.yStart = wn->y;
		w.xEnd = wn->x + wn->width;
		w.yEnd = wn->y + wn->height;
		return w;
	}

	/*-------------------------------------------*\
	|		Creating GUI Element Functions	   	  |
	\*-------------------------------------------*/

	Window* createWindow(const int x, const int y, const int width, const int height, const char* name)
	{
		Window* window = (Window*)malloc(sizeof(Window));

		window->width = width;
		window->height = height;
		window->x = (x == Centered ? (spWidth(ScreenSpace) / 2) - (width / 2) : x);
		window->y = (y == Centered ? (spHeight(ScreenSpace) / 2) - (height / 2) : y) + 3;

		window->beingHeld = false;

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

	Option* _createOption(Window* parentWindow, int x, int y, int width, int height)
	{
		Option* op = (Option*)malloc(sizeof(Option));

		for (int i = 0; i < TEXT_SIZE; i++)
			op->title[i] = 0;

		op->x = x, op->y = y;
		op->width = width;
		op->height = height;
		op->beingHeld = false;
		op->wasPressed = false;
		op->font = DefaultFont;
		op->type = NULL;

		op->_window = parentWindow;
		_addOption(op, parentWindow);

		return op;
	}

	Option* createButton(Window* parentWindow, int x, int y, int width, int height, const char* title)
	{
		Option* op = _createOption(parentWindow, x, y, width, height);
		strcpy(op->title, title);
		op->type = Button;

		return op;
	}

	Option* createTextBox(Window* parentWindow, int x, int y, const char* text, Font font)
	{
		Option* op = _createOption(parentWindow, x, y, txtWidth(text, font), txtHeight(text, font));
		strcpy(op->title, text);
		op->type = TextBox;
		op->font = font;

		return op;
	}

	Option* createSlider(Window* parentWindow, int x, int y, int width, int height, float slideStartLoc) // slide start loc is float between 0, and 100
	{
		Option* op = _createOption(parentWindow, x, y, width, height);
		op->sliderVal = clampFloat(slideStartLoc, 1, 100);
		op->type = Slider;

		return op;
	}

	/*-------------------------------------------*\
	|		Calculating GUI Element Functions  	  |
	\*-------------------------------------------*/

	bool calculateWindow(Window* window)
	{
		Space fullspace = { window->x, window->y - 3, window->x + window->width, window->y + window->height };
		Space titlebar = { window->x, window->y - 3, window->x + window->width, window->y };

		if (pointSpaceOverlap(Mouse.x, Mouse.y, titlebar) && key(LMB).pressed)
		{
			window->heldOffsetY = titlebar.yStart - Mouse.y + 3;
			window->heldOffsetX = titlebar.xStart - Mouse.x;
			window->beingHeld = true;
		}
		else if (!key(LMB).held)
			window->beingHeld = false;

		if (window->beingHeld)
		{
			window->x = Mouse.x + window->heldOffsetX;
			window->y = Mouse.y + window->heldOffsetY;
		}
		return pointSpaceOverlap(Mouse.x, Mouse.y, fullspace);
	}

	bool calculateButton(Option* button)
	{
		if (!pointSpaceOverlap(Mouse.x, Mouse.y, calcSpace(_windowSpace(button->_window), button->x, button->y, button->width, button->height)))
		{
			button->wasPressed = false;
			return button->beingHeld = false;
		}

		if (key(LMB).pressed)    button->beingHeld = true, button->wasPressed = true;
		else if (!key(LMB).held) button->beingHeld = false, button->wasPressed = false;
		else                     button->wasPressed = false;

		return button->beingHeld;
	}

	bool calculateSlider(Option* slider)
	{
		Space sp = calcSpace(_windowSpace(slider->_window), slider->x, slider->y, slider->width, slider->height);
		slider->sliderVal = clampFloat(slider->sliderVal, 1, 100);

		if (pointSpaceOverlap(Mouse.x, Mouse.y, sp) && key(LMB).held)
		{
			slider->sliderVal = map(Mouse.x, sp.xStart, sp.xEnd, 1, 100);
			return true;
		}
		return false;
	}

	/*-------------------------------------------*\
	|		 Drawing GUI Element Functions  	  |
	\*-------------------------------------------*/

	void _drawShade(int xStart, int yStart, int xEnd, int yEnd)
	{
		for (int y = yStart; y < yEnd; y++)
			for (int x = xStart; x < xEnd; x++)
			{
				Color r, g, b;
				calcXterm(getBackColor(x, y), &r, &g, &b);

				if (y == yStart || x == xStart)
					drawPixel(x, y, calcColor(r + 20, g + 20, b + 20));
				else if (y == yEnd - 1 || x == xEnd - 1)
					drawPixel(x, y, calcColor(r - 20, g - 20, b - 20));
			}
	}

	Space drawWindow(Window* window, bool dark)
	{
		Space windowSpace = drawRectFilled(window->x, window->y, window->width, window->height, dark ? DARK_WINDOW_COL : LIGHT_WINDOW_COL);
		sysDrawRect(windowSpace.xStart, windowSpace.yStart - 3, windowSpace.xEnd, windowSpace.yStart, Screen, true, Default, Default, dark ? DARK_TITLE_COL : LIGHT_TITLE_COL);
		_drawShade(windowSpace.xStart, windowSpace.yStart - 3, windowSpace.xEnd, windowSpace.yEnd);

		if (window->name != NULL)
			sysDrawText(windowSpace.xStart + 2, windowSpace.yStart - 2, Screen, window->name, DefaultFont, dark ? White : Black, Default);

		return windowSpace;
	}

	void drawOption(Option* op, bool dark)
	{
		Space spWindow = _windowSpace(op->_window);

		switch (op->type)
		{
		case Button:
		{
			Space s;
			if (op->beingHeld)
				s = spDrawRect(op->x, op->y, op->width, op->height, spWindow, true, dark ? DARK_BUT_ON_COL : LIGHT_BUT_ON_COL);
			else
				s = spDrawRect(op->x, op->y, op->width, op->height, spWindow, true, dark ? DARK_BUT_OF_COL : LIGHT_BUT_OF_COL);

			_drawShade(s.xStart, s.yStart, s.xEnd, s.yEnd);
			spDrawText(Centered, Centered, s, op->title, DefaultFont, Black);
		} break;

		case TextBox:
		{
			spDrawText(op->x, op->y, spWindow, op->title, op->font, dark ? DARK_TEXT_COl : LIGHT_TEXT_COL);
		} break;

		case Slider:
		{
			Space s = calcSpace(spWindow, op->x, op->y, op->width, op->height);
			spDrawRect(op->x, op->y, op->width, op->height, spWindow, true, dark ? DARK_SLIDEB_COL : LIGHT_SLIDEB_COL);
			int x = map(op->sliderVal, 1, 100, s.xStart, s.xEnd);
			spDrawRect(x, s.yStart, 1, op->height, ScreenSpace, true, dark ? DARK_SLIDEF_COL : LIGHT_SLIDEF_COL);
		} break;

		default:
			_Error("tried to draw invalid option.", __LINE__);
		}
	}

	Space drawWindowAndContents(Window* w, bool dark)
	{
		Space s = drawWindow(w, dark);
		for (int i = 0; i < w->numOps; i++)
			drawOption(w->ops[i], dark);
		return s;
	}

	/*-------------------------------------------*\
	|			  Delete Gui Elements			  |
	\*-------------------------------------------*/

	void deleteWindow(Window* wn)
	{
		for (int i = 0; i < wn->numOps; i++)
			free(wn->ops[i]);
		free(wn);
	}

#endif
#else
#error You need to use an ACRE 3.1 compatible Version
#endif

/* 


350 lines
283
* */