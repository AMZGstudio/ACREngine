#define FPS 200
#define SHOW_FPS true
#include "ACREngine.h"

#define SPACE_FROM_BOTTOM 8

Space drawPicture(Space canvas, int xWidth, int yStart, int yWidth)
{
	Space pic = sysDrawRect(Centered, yStart, xWidth, yStart + yWidth, canvas, Default, false, Default, Grey);
	sysDrawRect(1, 1, width(pic) - 1, height(pic) - 1, pic, Default, true, Default, Black);
	return pic;
}

void drawTitleBar(int* open)
{
	int x = 2, y = 0;
	char name[] = "File";

	if ((Mouse.y == y && Mouse.x >= x && Mouse.x <= x + strlen(name)) && (key(LeftM).pressed))
	{
		if (*open == 0) (*open) = -1;
		else (*open) = 0;
	}
	else if(key(LeftM).pressed)
		(*open) = -1;

	drawRect(0, 0, width(Screen), 0, Color(100, 100, 100));
	if (*open > -1)
	{
		sysDrawText(2, 0, Screen, "File", Default, Black, White);
		drawMenu(0, 2, Screen, 10, 1, (*open)-1, 2, White, Black, "Option 1", "Option 2");
		drawRectFilled(0, 1, 10, 3, Grey);
	}
	else
	{
		sysDrawText(2, 0, Screen, "File", Default, White, Default);
	}
}

void menu(Space box, int* menuSelected, int amountOptions, int menuSpacing)
{
	drawMenu(3, 2, box, box.endX - box.startX - 5, 3, *menuSelected, amountOptions, Black, White,
		"Frame 1", "Frame 2", "Frame 3", "Frame 4", "Frame 5", "Frame 6", "Frame 7", "Frame 8", "Frame 9", "Frame 10");

	// draw moving lines
	int optionSelectedCurrent = 0;
	for (int i = 0; i < amountOptions * menuSpacing; i += menuSpacing)
	{
		sysDrawPoint(1, i + 2, box, '-', Default, Default);

		//check for mouse input
		Space mouse = { Mouse.x, Mouse.y-2, Mouse.x, Mouse.y-2 }; // the -2 is just for formatting
		Space option = { box.startX, box.startY+i, box.endX, box.startY+i };

		if (spaceCollide(mouse, option) && key(LeftM).held)
		{
			(*menuSelected) = optionSelectedCurrent;
		}
		optionSelectedCurrent++;
	}
	
	if (key(Up).pressed) (*menuSelected)--;
	if (key(Down).pressed) (*menuSelected)++;
}

void drawButton(int xStart, int yStart, int xEnd, int yEnd, Space box, char* title, int color, int colorPressed)
{
	Space buttom = sysDrawRect(xStart, yStart, xEnd, yEnd, box, Default, true, Default, color);
	sysDrawText(Centered, Centered, buttom, title, Default, White, Default);
	
	Space mouse = { Mouse.x, Mouse.y, Mouse.x, Mouse.y };
	if (key(LeftM).held && spaceCollide(buttom, mouse)) 
		sysDrawRect(0, 0, width(buttom), height(buttom), buttom, Default, true, Default, colorPressed);
}

Space drawWindow(int xStart, int yStart, int xEnd, int yEnd, Space canvas, char* title)
{
	Space window = sysDrawRect(xStart, yStart, xEnd, yEnd, canvas, Default, true, Default, 239);
	sysDrawRect(0, 0, width(window), 0, window, Default, Default, Default, Grey);
	sysDrawText(2, 0, window, title, Default, White, Default);

	return window;
}

int main()
{
	initalize("GIF Maker - Uriel", 140, 70, 8, 8, Default, Color(30, 30, 30));
	int menuSelected = 0;
	int amountOptions = 10;
	int menuSpacing = 3;

	int boxXStart = 2, boxYStart = 2;
	int picXWidth = 90, picYStart = 2;

	int fileMenuOpen = -1;

	while (true)
	{
		ShowCursor(0);
		drawTitleBar(&fileMenuOpen);

		Space canvas = { 0, 2, Screen.endX, Screen.endY };
		Space pic = drawPicture(canvas, picXWidth, picYStart, 60);
		Space box = drawWindow(2, 2, 20, canvas.endY - SPACE_FROM_BOTTOM, canvas, "Frames");

		drawButton(Centered, box.endY-box.startY-5, 12, box.endY - box.startY - 3, box, "Delete", Grey, DarkGrey);
		
		Space controlPanel =  drawWindow(canvas.endX - 22, canvas.startY, canvas.endX - 3, canvas.endY - 55, canvas, "Color Selector");
		Space propertyPanel = drawWindow(canvas.endX - 22, canvas.endY-30, canvas.endX - 3, canvas.endY - SPACE_FROM_BOTTOM, canvas, "Properties");
		
		int colorRed = 255, colorBlue = 0, colorGreen = 0;

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				if (x == 0)
				{
					sysDrawPoint()
				}
				//sysDrawPoint(x, y, controlPanel, Default, Default, Color(colorRed, 255-map(y, 0, 20, 0, 255)- map(x, 0, 20, 0, 255), 255 - map(y, 0, 20, 0, 255) - map(x, 0, 20, 0, 255)));
				render(false);
			}
		}
			

		sysDrawText(1, 2, propertyPanel, "Path:\n\nC:/my_files/hello\n\nLength: 200", Default, White, Default);
		
		drawButton(Centered, 9, 15, 11, propertyPanel, "Change Length", Grey, DarkGrey);
		drawButton(Centered, 14, 15, 16, propertyPanel, "Change Path", Grey, DarkGrey);

		menu(box, &menuSelected, amountOptions, menuSpacing);

		//drawPoint(Mouse.x, Mouse.y, Yellow);

		render(true);
	}
	return terminate();
}