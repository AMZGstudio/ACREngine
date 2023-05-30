#define FPS 60
#include "ACREngine.h"

void drawPillar(int xStart, int yStart, bool topHalf, Image pipe, Image pipePillar)
{
	drawImage(xStart, yStart, pipe);
	if (topHalf == false)
		for (int i = yStart + 12; i <= Screen.endY; i++)
			drawImage(xStart, i, pipePillar);
	else
		for (int i = yStart -1; i >= 0; i--)
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

	*override = true, *score = 0, * birdPosition = height(Screen) / 2;
	pillarsX[0] = 250, pillarsX[1] = 330, pillarsX[2] = 410, pillarsX[3] = 490;
}

int main()
{
	initalize("Flappy Bird", 200, 100, 6, 6, Default, Cyan);
	Image birdUp = createImage("../Sprites/birdUp.acre"), birdDown = createImage("../Sprites/birdDown.acre"), pipe = createImage("../Sprites/pipe.acre"), pipePillar = createImage("../Sprites/pipePillar.acre");

	float birdPosition = height(Screen) / 2, birdVelocity = 0.0f, birdAcceleration = 0.0f, gravity = 0.05f;
	int pillarsY[4] = { 20, 30, 15, 35 }, pillarsX[4] = { 250, 330, 410, 490 }, amountPillars = 4, pillarGap = 80, pillarWidth = 26, score = 0;
	
	bool override = true, point = false, endGame = false;
	clock_t timeOld = 0;

	drawInt(3, 3, score, EightBit, Black);
	drawImage((int)(width(Screen) / 3), (int)birdPosition, birdUp);
	render(true);

	while (!key(A).pressed);
	while (true)
	{
		if ((key(A).pressed || override) && birdVelocity > gravity + 0.05f) override = false, birdAcceleration = 0.0f, birdVelocity = -1.3f;
		else birdAcceleration += gravity;
	
		if (birdAcceleration >= gravity) birdAcceleration = gravity;

		birdVelocity += birdAcceleration;
		if(birdPosition + birdVelocity > 1) birdPosition += birdVelocity;
		
		if(birdVelocity > 0) drawImage((int)(width(Screen) / 3), (int)birdPosition, birdUp);
		else drawImage((int)(width(Screen) / 3), (int)birdPosition, birdDown);
		
		drawInt(3, 3, score, EightBit, Black);
		for (int i = 0; i < amountPillars; i++)
		{
			drawPillar(pillarsX[i], pillarsY[i], true, pipe, pipePillar);
			drawPillar(pillarsX[i], pillarsY[i] + 50, false, pipe, pipePillar);
			
			if (birdPosition > height(Screen)) endGame = true;

			if (rectangleCollide((int)(width(Screen) / 3), (int)birdPosition, (int)(width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], 1, pillarsX[i] + 26, pillarsY[i] + 12) ||
				rectangleCollide((int)(width(Screen) / 3), (int)birdPosition, (int)(width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], pillarsY[i] + 50, pillarsX[i] + 26, height(Screen))) endGame = true;
			
			else if (rectangleCollide((int)(width(Screen) / 3), (int)birdPosition, (int)(width(Screen) / 3) + 15, (int)birdPosition + 12, pillarsX[i], 1, pillarsX[i] + 26, height(Screen)) && clock() > timeOld + 900)
			{
				score++, point = true;
				timeOld = clock();
			}
			pillarsX[i]--;
			if (pillarsX[i] + pillarGap < 0) pillarsX[i] += width(Screen) + pillarGap * 2;
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
				drawImage((int)(width(Screen) / 3), birdPosition, birdUp);
				
				birdPosition+=2;
			} while (birdPosition < height(Screen) + 5);
			askToPlayAgain(pillarsX, &birdPosition, &score, &override);
		}
		render(true);
	}
	while (!key(A).pressed);
}