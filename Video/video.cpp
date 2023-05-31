#define ACRE_START
#define SHOW_FPS

#include "../ACREngine.h"
#include "escapi.h"

typedef struct Pixel {
	int r, g, b;
} Pixel;
void getColor(Pixel* out, Pixel in, Pixel* allowedCols, int w)
{
	Pixel prevCol = { 0,0,0 };
	float distance = 0;
	int lastDistnace = 2000;

	for (int i = 0; i < w; i++)
	{
		//if (abs(allowedCols[i] - col) < lastDistnace)
		//{
			//lastDistnace = abs(allowedCols[i] - col);
			//thatCol = allowedCols[i];
		//}
	}
	//*colN = thatCol;
}
void drawVideoFrame(float zoom, int xr, int yr, int* data, int capW, int capH, bool flip)
{
	for (int x = 0; x < capW; x++)
	{
		int realY = 0;

		int y = flip ? capH - 1 : 0;
		while (true)
		{
			if (flip && y < 0) break;
			if (!flip && y >= capH) break;

			int id = y * capW + x;
			int val = data[id];

			Pixel p;
			p.r = clamp(((val >> (8 * 2)) & 0xff) + 10, 0, 255);
			p.g = clamp(((val >> (8 * 1)) & 0xff), 0, 255);
			p.b = clamp(((val >> (8 * 0)) & 0xff), 0, 255);

			Pixel o;
			Pixel allowed[3] = { {255, 0, 0}, {0, 255, 0}, {0, 255, 0} };
			//int col = ((0.3 * p.b) + (0.59 * g) + (0.11 * b));

			getColor(&o, p, allowed, 3);
			drawPoint(xr + x * zoom, yr + realY * zoom, Color(o.r, o.g, o.b));

			y += flip ? -1 : 1;
			realY += 1;
		}
	}
}

int main()
{
	initalize("Video", 320, 240, 3, 3, Default, Default);
	float zoom = 1.0f;
	bool flip = false;
	if (setupESCAPI() == 0) return 0;

	SimpleCapParams capture = { new int[3200*2400], 300,220 };
	if (initCapture(0, &capture) == 0) return 0;

	while (true)
	{

		// Capture webcam image
		doCapture(0); while (isCaptureDone(0) == 0) {}

		if (key(W).held) zoom += timePerSec(0.5);
		if (key(S).held) zoom -= timePerSec(0.5);

		bool press = key(LeftM).pressed;

		if (key(A).pressed) flip = true;
		if (key(Q).pressed) flip = false;
		
		drawVideoFrame(zoom, Mouse.x, Mouse.y, capture.mTargetBuf, capture.mWidth, capture.mHeight, flip);
	
		render(true);
	}
	return terminate();
}