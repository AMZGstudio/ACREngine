#define SHOW_FPS

#define ACRE_START
#include "../ACREngine.h"

#define ACRE_TRANSFORM
#include "../ACRE_Transform.h"

#define ACRE_FONTS
#include "../ACRE_Fonts.h"

#define ACRE_GUI
#include "../ACRE_Gui.h"

//Space getCanvasSpace(int width, int height, float zoom)
//{
//	float realWidth = width * zoom;
//	float realHeight = height * zoom;
//
//	float middleX = center(realWidth, Screen, X);
//	float middleY = center(realHeight, Screen, Y);
//
//	Space canvas = { middleX, middleY, middleX + realWidth, middleY + realHeight };
//	return canvas;
//}
//
//void drawColorBox(int r2, int g2, int b2, int xStart, int yStart, int width, int height, Space win, int* mCol)
//{
//	int r1 = 255, b1 = 255, g1 = 255;
//
//	float rs = r1, bs = b1, gs = g1; // s = selected
//	float rd = r2 - r1, bd = b2 - b1, gd = g2 - g1; // d = distance (how much it changed)
//	float ri = rd / width, bi = bd / width, gi = gd / width; // i = increase (rate of increase)
//
//	for (int x = 0; x <= width; x++)
//	{
//		int r1t = rs, b1t = bs, g1t = gs;
//		int r2t = 0, b2t = 0, g2t = 0;
//
//		float rst = r1t, bst = b1t, gst = g1t;
//		float rdt = r2t - r1t, bdt = b2t - b1t, gdt = g2t - g1t;
//		float rit = rdt / height, bit = bdt / height, git = gdt / height;
//
//		for (int y = 0; y <= height; y++)
//		{
//			drawPoint(win.startX + xStart + x, win.startY + yStart + y, Color(rst, gst, bst));
//			if (Mouse.x == win.startX + xStart + x && Mouse.y == win.startY + yStart + y && key(LeftM).held)
//				*mCol = Color(rst, gst, bst);
//
//			rst += rit;
//			bst += bit;
//			gst += git;
//		}
//		rs += ri;
//		bs += bi;
//		gs += gi;
//	}
//}
//
//void drawColorSegment(int numPixels, int xStart, int yStart, Space win, int r1, int g1, int b1, int whichToIncrement, float incrementAmount, int* ro, int* go, int* bo)
//{
//	int amountPixDone = 0;
//	int allCols[3] = { r1, g1, b1 };
//	while (amountPixDone <= numPixels)
//	{
//		drawPoint(win.startX + xStart, win.startY + yStart, Color(allCols[0], allCols[1], allCols[2]));
//		drawPoint(win.startX + xStart + 1, win.startY + yStart, Color(allCols[0], allCols[1], allCols[2]));
//
//		if ((Mouse.x == win.startX + xStart || Mouse.x == win.startX + xStart + 1) && Mouse.y == win.startY + yStart && key(LeftM).held)
//		{
//			*ro = allCols[0], * go = allCols[1], * bo = allCols[2];
//		}
//		allCols[whichToIncrement] += incrementAmount;
//		amountPixDone++;
//		yStart++;
//	}
//}
//
//void drawColorSelector(int xStart, int yStart, int width, int height, Window* window, bool dark, int* selectedR, int* selectedG, int* selectedB, int* mCol)
//{
//	Space win = drawWindow(window, dark);
//	calculateWindow(window);
//
//	float pixPerCol = (float)height / 6.0f;
//	float incrementAmount = 255.0f / pixPerCol;
//
//	drawColorSegment(pixPerCol, xStart, yStart + 0 * pixPerCol, win, 255, 0, 0, 1, incrementAmount, selectedR, selectedG, selectedB);
//	drawColorSegment(pixPerCol, xStart, yStart + 1 * pixPerCol, win, 255, 255, 0, 0, -incrementAmount, selectedR, selectedG, selectedB);
//	drawColorSegment(pixPerCol, xStart, yStart + 2 * pixPerCol, win, 0, 255, 0, 2, incrementAmount, selectedR, selectedG, selectedB);
//	drawColorSegment(pixPerCol, xStart, yStart + 3 * pixPerCol, win, 0, 255, 255, 1, -incrementAmount, selectedR, selectedG, selectedB);
//	drawColorSegment(pixPerCol, xStart, yStart + 4 * pixPerCol, win, 0, 0, 255, 0, incrementAmount, selectedR, selectedG, selectedB);
//	drawColorSegment(pixPerCol, xStart, yStart + 5 * pixPerCol, win, 255, 0, 255, 2, -incrementAmount, selectedR, selectedG, selectedB);
//
//	drawColorBox(*selectedR, *selectedG, *selectedB, xStart + 4, yStart, width, height, win, mCol);
//	drawRectFilled(win.startX + 2, win.endY - 4, win.startX + 4, win.endY - 2, *mCol);
//}
//
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//void getBuffSize(int* colorBuffer, int* width, int* height)
//{
//	if (colorBuffer != NULL)
//		free(colorBuffer);
//
//	char inputWidth[10] = { 0 };
//	char inputHeight[10] = { 0 };
//	while (textBoxInput(inputWidth, 10))
//	{
//		drawText(Centered, 10, "Enter Canvas Width", EightBit, Grey);
//		drawText(Centered, Centered, inputWidth, EightBit, Grey);
//		render(true);
//	}
//	while (textBoxInput(inputHeight, 10))
//	{
//		drawText(Centered, 10, "Enter Canvas Height", EightBit, Grey);
//		drawText(Centered, Centered, inputHeight, EightBit, Grey);
//		render(true);
//	}
//	*width = strToInt(inputWidth);
//	*height = strToInt(inputHeight);
//}
//
//void drawToolSelector(Window* win, int* toolSelected, int* prevSelected, bool dark, Image* allImgs, int amntImages)
//{
//	int amntTools = 3;
//	Space window = getWindowSpace(win);
//
//	for (int x = 0; x < 2; x++)
//		for (int y = 0; y < amntTools; y++)
//		{
//			Space rect;
//			int realY = map(y, 0, amntTools, 3, win->height);
//			int realX = map(x, 0, 2, 3, win->width);
//
//			if ((y + amntTools * x) == *toolSelected)
//				rect = sysDrawRect(realX, realY, realX + 8, realY + 8, window, Default, true, Default, dark ? DARK_BUTTON_PRESSED_COL : LIGHT_BUTTON_PRESSED_COL);
//			else
//				rect = sysDrawRect(realX, realY, realX + 8, realY + 8, window, Default, true, Default, dark ? DARK_BUTTON_COLOR : LIGHT_BUTTON_COLOR);
//			if ((y + amntTools * x) < amntImages)
//				sysDrawImage(Centered, Centered, rect, allImgs[(y + amntTools * x)]);
//
//			if (pointSpaceCollide(Mouse.x, Mouse.y, rect))
//				if (key(LeftM).held)
//					*toolSelected = (y + amntTools * x), * prevSelected = (y + amntTools * x);
//
//		}
//	if (key(B).pressed)
//		*toolSelected = 0;
//	if (key(E).pressed)
//		*toolSelected = 1;
//	if (key(P).pressed)
//		*toolSelected = 3;
//	if (key(Alt).pressed)
//		*prevSelected = *toolSelected;
//
//	if (key(Alt).held)
//		*toolSelected = 2;
//
//	else if (toolSelected == 2)
//		*toolSelected = *prevSelected;
//}
//
//void drawCanvas(float zoom, int* buffer, int bufWidth, int bufHeight)
//{
//	Space canvas = getCanvasSpace(bufWidth, bufHeight, zoom);
//	if (canvas.endX - canvas.startX > 0)
//	{
//		drawRectFilled(canvas.startX, canvas.startY, canvas.endX, canvas.endY, Grey);
//		drawRect(canvas.startX - 1, canvas.startY - 1, canvas.endX + 1, canvas.endY + 1, DarkGrey);
//
//	}
//	float newWidth = bufWidth * zoom;
//	float newHeight = bufHeight * zoom;
//
//	int xs = center(newWidth, Screen, X);
//	int ys = center(newHeight, Screen, Y);
//
//	for (int x = 0; x < bufWidth; x++)
//		for (int y = 0; y < bufHeight; y++)
//		{
//			if (buffer[y * bufWidth + x] != Default)
//				drawRectFilled(xs + (x * zoom), ys + (y * zoom), xs + ((x + 1) * zoom), ys + ((y + 1) * zoom), buffer[y * bufWidth + x]);
//		}
//
//}
//
//void mouseOnCanvasPos(int width, int height, float zoom, int* posx, int* posy)
//{
//	float newWidth = width * zoom;
//	float newHeight = height * zoom;
//	float realX = ((Mouse.x - (Width(Screen) / 2) + (newWidth / 2)) / zoom);
//	float realY = ((Mouse.y - (Height(Screen) / 2) + (newHeight / 2)) / zoom);
//
//	*posx = realX;
//	*posy = realY;
//}
//
//bool legalMousePos(int width, int height, float zoom)
//{
//	Space canvas = getCanvasSpace(width, height, zoom);
//	if (Mouse.x >= canvas.startX && Mouse.x < canvas.endX && Mouse.y >= canvas.startY && Mouse.y < canvas.endY)
//		return true;
//
//	return false;
//}
//
//void paintBucket(int x, int y, int color, int surfaceColor, int* colorBuffer, int bufWidth, int bufHeight)
//{
//	if (x >= bufWidth || x < 0 || y >= bufHeight || y < 0)
//		return;
//
//	if (colorBuffer[y * bufWidth + x] != surfaceColor || colorBuffer[y * bufWidth + x] == color)
//		return;
//
//	colorBuffer[y * bufWidth + x] = color;
//
//	paintBucket(x + 1, y, color, surfaceColor, colorBuffer, bufWidth, bufHeight);
//	paintBucket(x - 1, y, color, surfaceColor, colorBuffer, bufWidth, bufHeight);
//	paintBucket(x, y + 1, color, surfaceColor, colorBuffer, bufWidth, bufHeight);
//	paintBucket(x, y - 1, color, surfaceColor, colorBuffer, bufWidth, bufHeight);
//}
//
//int eyeDropper(int width, int height, int* colorBuf, float zoom)
//{
//	int posx, posy;
//	mouseOnCanvasPos(width, height, zoom, &posx, &posy);
//
//	return colorBuf[(int)posy * width + (int)posx];
//}
//
//int main()
//{
//	bool darkMode = true;
//	initalize("ACRE Painter", 300, 180, 4, 4, Black, darkMode ? Color(30, 30, 30) : Color(160, 160, 160));
//
//	float zoom = 1.0f;
//
//	int width = 0, height = 0;
//	int* colorBuffer = NULL;
//	int sred = 255, sgreen = 0, sblue = 0;
//
//	int selectedColor = Black;
//	int colorSelectorWidth = 20;
//	int toolSelected = 0;
//	int prevSelected = 0;
//
//	Timer timer = createTimer();
//	Image allImgs[4] = { loadImage("paintBrush.acre"), loadImage("eraser.acre"), loadImage("eyedropper.acre"), loadImage("paintbucket.acre") };
//
//	Window* colors = createWindow(2, 2, colorSelectorWidth + 9, 50, "Color Picker", false);
//	Window* preview = createWindow(Width(Screen) - 28, 2, 25, 30, "Preview Panel", false);
//	Window* controls = createWindow(Width(Screen) - 28, Height(Screen) - 40, 25, 30, "Controls", false);
//	Window* tools = createWindow(2, Height(Screen) - 45, colorSelectorWidth + 9, 41, "Tools", false);
//
//	while (true)
//	{
//		drawCanvas(zoom, colorBuffer, width, height);
//
//		calculateWindow(preview);
//		calculateWindow(controls);
//		calculateWindow(tools);
//		drawWindow(preview, darkMode);
//		drawWindow(controls, darkMode);
//		drawWindow(tools, darkMode);
//
//		drawColorSelector(2, 3, colorSelectorWidth, 36, colors, darkMode, &sred, &sgreen, &sblue, &selectedColor);
//		drawToolSelector(tools, &toolSelected, &prevSelected, darkMode, allImgs, 4);
//
//		Space windowPreview = { preview->x, preview->y, preview->x + preview->width, preview->y + preview };
//		sysDrawColorBuffer(Centered, 3, windowPreview, colorBuffer, width, height);
//
//		if (drawButton(controls, Centered, 12, 17, 17, "New", darkMode))
//		{
//			getBuffSize(colorBuffer, &width, &height);
//
//			colorBuffer = malloc(sizeof(int) * width * height);
//			for (int i = 0; i < width * height; i++)
//				colorBuffer[i] = Default;
//		}
//		if (drawButton(controls, Centered, 4, 17, 9, "Save", darkMode))
//			save(colorBuffer, width, height);
//
//		int mposx = 0, mposy = 0;
//		mouseOnCanvasPos(width, height, zoom, &mposx, &mposy);
//
//		if (key(LeftM).held && legalMousePos(width, height, zoom))
//		{
//			if (toolSelected == 0)
//				colorBuffer[(int)mposy * width + (int)mposx] = selectedColor;
//
//			if (toolSelected == 1)
//				colorBuffer[(int)mposy * width + (int)mposx] = Default;
//
//			if (toolSelected == 2)
//			{
//				selectedColor = eyeDropper(width, height, colorBuffer, zoom);
//			}
//			if (toolSelected == 3)
//			{
//				int mposx = 0, mposy = 0;
//				mouseOnCanvasPos(width, height, zoom, &mposx, &mposy);
//
//				paintBucket(mposx, mposy, selectedColor, colorBuffer[(int)mposy * width + (int)mposx], colorBuffer, width, height);
//			}
//		}
//
//		calculateTimer(&timer);
//		if (Mouse.scrollH > 0)
//		{
//			zoom += timePerSec(30);
//			timer.elapsedTime = 0;
//		}
//		else if (Mouse.scrollH < 0 && zoom > 1.0f)
//		{
//			zoom -= timePerSec(30);
//			timer.elapsedTime = 0;
//		}
//		if (timer.elapsedTime > 0.1)
//		{
//			zoom = (int)(zoom + 0.5);
//		}
//		render(true);
//	}
//	return terminate();
//}


int main()
{
	initalize("Sprite Editor", 220, 160, 4, 4, Default, VeryDarkGrey);

	Area a = createArea(10, 10, Default, Default);
	AreaTrans at = createAreaTrans(a);

	at.x = Width(Screen) / 2, at.y = Height(Screen) / 2;

	while (true)
	{
		Space sp = drawRectFilled(0, 0, 40, Height(Screen), DarkGrey);

		if(drawButton(sp, Centered, 1, "New", Foant))
			

		drawAreaTransformed(at, Screen);
		render(true);
	}
	return terminate();
}