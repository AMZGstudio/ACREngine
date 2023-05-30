#define ACRE_START
#define SHOW_FPS

#include <time.h>
#include "../Files/ACREngine.h"

void drawPillar(int xStart, int yStart, bool topHalf, Image pipe, Image pipePillar)
{
	drawImage(xStart, yStart, pipe);
	if (topHalf == false)
		for (int i = yStart + 12; i <= Screen.endY; i++)
			drawImage(xStart, i, pipePillar);
	else
		for (int i = yStart - 1; i >= 0; i--)
			drawImage(xStart, i, pipePillar);
}

void askToPlayAgain(int pillarsX[4], float* birdPosition, int* score, bool* override)
{
	char scoreChar[10] = { 0 }, message[15] = "Score:";
	_itoa(*score, scoreChar, 10);
	strcat(message, scoreChar);

	Space window = drawRectFilled(Centered, Centered, strlen(message) * 8 + 14, 30, 94);

	drawRect(Centered, Centered, strlen(message) * 8 + 14, 30, White);
	sysDrawText(Centered, Centered, window, message, EightBit, Default, White);
	render(false);

	while (!key(A).pressed);

	*override = true, * score = 0, * birdPosition = Height(Screen) / 2;
	pillarsX[0] = 250, pillarsX[1] = 330, pillarsX[2] = 410, pillarsX[3] = 490;
}

int main()
{
	initalize("Flappy Bird", 200, 100, 6, 6, Default, Cyan);
	Image birdUp = loadImage("../Sprites/birdUp.acre");
	Image birdDown = loadImage("../Sprites/birdDown.acre");
	Image pipe = loadImage("../Sprites/pipe.acre");
	Image pipePillar = loadImage("../Sprites/pipePillar.acre");

	float birdPosition = Height(Screen) / 2, birdVelocity = 0.0f, birdAcceleration = 0.0f, gravity = 0.05f;
	int pillarsY[4] = { 20, 30, 15, 35 }, pillarsX[4] = { 250, 330, 410, 490 }, amountPillars = 4, pillarGap = 80, pillarWidth = 26, score = 0;

	bool override = true, point = false, endGame = false;
	clock_t timeOld = 0;

	while (!key(A).pressed)
	{
		drawInt(3, 3, score, EightBit, Black);
		drawImage(Width(Screen) / 3, birdPosition, birdUp);
		render(true);
	}

	while (!key(Esc).pressed)
	{
		if ((key(A).pressed || override) && birdVelocity > gravity + 0.05f) 
			override = false, birdAcceleration = 0.0f, birdVelocity = -1.3f;
		else 
			birdAcceleration += gravity;

		if (birdAcceleration >= gravity) 
			birdAcceleration = gravity;

		birdVelocity += birdAcceleration;

		if (birdPosition + birdVelocity > 1) 
			birdPosition += timePerSec(birdVelocity*10);

		if (birdVelocity > 0) 
			drawImage((int)(Width(Screen) / 3), (int)birdPosition, birdUp);
		else 
			drawImage((int)(Width(Screen) / 3), (int)birdPosition, birdDown);

		drawInt(3, 3, score, EightBit, Black);
		for (int i = 0; i < amountPillars; i++)
		{
			drawPillar(pillarsX[i], pillarsY[i], true, pipe, pipePillar);
			drawPillar(pillarsX[i], pillarsY[i] + 50, false, pipe, pipePillar);

			if (birdPosition > Height(Screen)) endGame = true;

			if (rectangleCollide((int)(Width(Screen) / 3), (int)birdPosition, (int)(Width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], 1, pillarsX[i] + 26, pillarsY[i] + 12) ||
				rectangleCollide((int)(Width(Screen) / 3), (int)birdPosition, (int)(Width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], pillarsY[i] + 50, pillarsX[i] + 26, Height(Screen))) endGame = true;

			else if (rectangleCollide((int)(Width(Screen) / 3), (int)birdPosition, (int)(Width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], 1, pillarsX[i] + 26, Height(Screen)) && clock() > timeOld + 900)
			{
				score++, point = true;
				timeOld = clock();
			}
			pillarsX[i] -= timePerSec(1);

			if (pillarsX[i] + pillarGap < 0) 
				pillarsX[i] += Width(Screen) + pillarGap * 2;
		}
		if (endGame)
		{
			endGame = false;
			do
			{
				render(true);
				for (int i = 0; i < amountPillars; i++)
				{
					drawPillar(pillarsX[i], pillarsY[i], true, pipe, pipePillar);
					drawPillar(pillarsX[i], pillarsY[i] + 50, false, pipe, pipePillar);
				}
				drawImage((int)(Width(Screen) / 3), birdPosition, birdUp);

				birdPosition += 2;
			} while (birdPosition < Height(Screen) + 5);
			askToPlayAgain(pillarsX, &birdPosition, &score, &override);
		}
		render(true);
	}
	while (!key(A).pressed);
}