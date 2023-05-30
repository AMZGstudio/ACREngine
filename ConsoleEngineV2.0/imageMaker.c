#include "ConsoleEngine.h"
#define Blank -1
#define SPACE_RIGHT 20
#define PIXEL_ON_SCREEN 9

void getDimensions(int* width, int* height)
{
	char output1[100] = { 0 }, output2[100] = { 0 };
	while (!key(EnterKey).pressed)
	{
		Space window = drawWindow(White, Default, Screen, false, Centered, Centered, 20, 3);
		drawText(White, Default, window, "Enter Width", Centered, -1);
		textBoxInput(White, Default, window, output1, window.endX - window.startX, 1, 1);
		render(true);
	}
	while (!key(EnterKey).pressed)
	{
		Space window = drawWindow(White, Default, Screen, false, Centered, Centered, 20, 3);
		drawText(White, Default, window, "Enter Height", Centered, -1);
		textBoxInput(White, Default, window, output2, window.endX - window.startX, 1, 1);
		render(true);
	}
	*width = atoi(output1), * height = atoi(output2);
}

int main()
{
	int width, height, selectedColor = 0;

	initalize(Default, 100, 40, 8, 14, Default, Color(50, 50, 50));
	getDimensions(&width, &height);
	initalize(Default, width*(PIXEL_ON_SCREEN+1) + SPACE_RIGHT, height * (PIXEL_ON_SCREEN + 2), 7, 7, Default, Default);

	int* pixels = malloc(sizeof(int) * width * height);

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			pixels[y * width + x] = Blank;

	while (true)
	{
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				if (pixels[y*width+x] == Blank)
					 drawRect(Default, Red, Screen, 'x', true, map(x, 0, 9, 1, 100) + 1, map(y, 0, 9, 1, 100) + 1, map(x, 0, 9, 1, 100) + PIXEL_ON_SCREEN, map(y, 0, 9, 1, 100) + PIXEL_ON_SCREEN);
				else drawRect(Default, pixels[y * width + x], Screen, ' ', true, map(x, 0, 9, 1, 100) + 1, map(y, 0, 9, 1, 100) + 1, map(x, 0, 9, 1, 100) + PIXEL_ON_SCREEN, map(y, 0, 9, 1, 100) + PIXEL_ON_SCREEN);
		
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				if ((Mouse.x > map(x, 0, 9, 1, 100) && Mouse.x < map(x, 0, 9, 1, 100) + 9) && (Mouse.y > map(y, 0, 9, 1, 100) && Mouse.y < map(y, 0, 9, 1, 100) + 9))
					if (key(LeftM).held)
						pixels[y*width+x] = Blue;
		
		render(true);
	}

	while (!key(SpaceKey).pressed);
	return terminate();
}