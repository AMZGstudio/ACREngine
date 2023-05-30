#define WAIT 15
#define PADDLE_HEIGHT 10
#define FULLSCREEN true
#include "ConsoleEngine.h"

bool checkCol(int paddleX, int paddleY, int paddleX2, int paddleY2, float ballX, float ballY)
{
	if ((ballX + 1 >= paddleX) && (ballX - 1 <= paddleX2) && (ballY - 1 >= paddleY) && (ballY + 1 <= paddleY2)) return true;
	else return false;
}
clock_t frozenStart = 0;
int main()
{
	srand(time(0));
	initalize("Pong", 100, 50, 10, 10, Default, Black);
	int paddleHR = 1, paddleHL = 1;
	int paddleDR = 1, paddleDL = 1;
	int pointsRight = 0, pointsLeft = 0;
	float ballVX = 1.5, ballVY = 0.5;
	float ballX1 = center(3, 1, width()), ballY1 = center(3, 1, height());
	int color = White;

	bool frozen = false;
	while (!key(EscapeKey).pressed)
	{
		float ballX2 = ballX1 + 3, ballY2 = ballY1 + 3;
		color = White;
		if (rectangleCollide((int)ballX1, (int)ballY1, (int)ballX2, (int)ballY2, 2, paddleHL, 4, paddleHL + PADDLE_HEIGHT)) ballVX *= -1, ballX1 = 4;
		if (rectangleCollide((int)ballX1, (int)ballY1, (int)ballX2, (int)ballY2, width()-3, paddleHR, width()-1, paddleHR + PADDLE_HEIGHT)) ballVX *= -1, ballX1 = width()-3-2;

		drawNumber(pointsRight, width() / 2 - 1, 2, Default, Default);
		drawNumber(pointsLeft, width() / 2 + 1, 2, Default, Default);
		drawSquare(1, 1, 100, 50, Default, Black);
		drawSquare(2, paddleHL, 3, paddleHL + PADDLE_HEIGHT, Default, White);
		drawSquare(width()-2, paddleHR, width()-1, paddleHR + PADDLE_HEIGHT, Default, White);

		if (ballY1 <= 1 || ballY2 >= height() + 1) ballVY *= -1;
		
		if (ballX1 > width() + 10)
		{
			ballX1 = center(3, 1, width()), ballY1 = center(3, 1, height()), ballVY = 0, ballVX = 0;
			frozenStart = clock(); frozen = true;
			pointsRight++;
		}
		if (ballX1 < -10)
		{
			ballX1 = center(3, 1, width()), ballY1 = center(3, 1, height()), ballVY = 0, ballVX = 0;
			frozenStart = clock(); frozen = true;
			pointsLeft++;
		}
		int newTime = (int)frozenStart + (int)300;
		int timeToPass = (int)clock();
		
		ballX2 = ballX1 + 2, ballY2 = ballY1 + 2;

		if (timeToPass > newTime && frozen)
		{
			frozen = false;
			ballVY = 0.5, ballVX = 1.5;
			if (rand() % 2) ballVY *= -1;
			if (rand() % 2) ballVX *= -1;
		}
		drawSquare((int)ballX1, (int)ballY1, (int)ballX2, (int)ballY2, Default, color);
		drawChar('/', ballX1, ballY1, Default, Black);
		drawChar('\\', ballX2, ballY1, Default, Black);
		drawChar('\\', ballX1, ballY2, Default, Black);
		drawChar('/', ballX2, ballY2, Default, Black);

		ballX1 += ballVX, ballY1 += ballVY;

		if (key(W).held && paddleHL > 1) paddleHL--;
		if (key(S).held && paddleHL + PADDLE_HEIGHT < height()) paddleHL++;

		if (key(O).held && paddleHR > 1) paddleHR--;
		if (key(L).held && paddleHR + PADDLE_HEIGHT < height()) paddleHR++;
		render(true);
	}
	return terminate();
}