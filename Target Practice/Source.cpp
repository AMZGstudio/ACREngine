#define ACRE_START
#define SHOW_FPS
#include "../ACRE Files/ACREngine.h"

enum types {Arrow, Target};



enum gameState {Start, Run, MoveArrow, MoveTarget};

class Objects
{
public:
	float _x, _y, _speed; int _type;
	bool started, stopped;
	
	Objects(int type)
	{
		stopped = false, started = false;
		_type = type;
		_x = Width(Screen) / 2, _y = Height(Screen) / 2,_speed = 100;
	}

	void refresh()
	{
		*this = Objects(_type);
	}

	void updateObject()
	{
		if (key(Spacebar).pressed)
		{
			if (started) stopped = true;
			started = true;
		}

		if (_x >= Width(Screen)) _x = 0;
		if (_x <= 0) _x = Width(Screen);
	
		if (started && !stopped)
			_x += _type == Target ? timePerSec(_speed) : -timePerSec(_speed /2);	
	}

	void drawObject() //type number will refer to which object it will be
	{
		if (_type == Target)
		{
			drawCircleFilled(_x, _y, 6, Red);
			drawCircle(_x, _y, 3, White);
			drawCircle(_x, _y, 5, White);
			drawCircle(_x, _y, 1, White);
		}

		if (_type == Arrow) //Arrow
		{
			drawCircle(_x, _y, 1, Grey);
			drawPixel(_x, _y, Brown);
		}
	}
};

int main()
{
	initialize("Target Game", 250, 125, 3, 3, Default, Default);

	Objects arrow(Arrow);
	Objects target(Target);

	int score = 0;
	int bestHit = 0;
	int state = Start;
	int scoreUp = -1;

	int hitY = -1;
	bool startGame = true;
	bool gameOver = false;

	Timer timer = createTimer();

	while (!key(Esc).pressed)
	{
		if (state == Start)
		{
			target.refresh();
			arrow.refresh();
			startGame = false;
			hitY = -1;
			state = Run;
		}
		if (state == Run)
		{
			target.drawObject();

			if (!target.stopped)
				target.updateObject();

			else
			{
				arrow.updateObject();
				arrow.drawObject();
			}

			if (arrow.stopped && !gameOver)
			{
				scoreUp = 6 - abs((int)(arrow._x - target._x));
				scoreUp = clamp(scoreUp, 0, 10);

				if (scoreUp > bestHit) bestHit = scoreUp;

				score += scoreUp;
				hitY = target._y;
				gameOver = true;
			}
			if (hitY != -1)
			{
				drawNumber(target._x, hitY, scoreUp, EightBit, Green);
				hitY -= timePerSec(50);
			}
			if (hitY < target._y - 40)
			{
				hitY = -1;
			}

			
			if (gameOver && hitY == -1)
			{
				while(!key(Spacebar).pressed) {}
			
				gameOver = false;
				state = Start;
			}
		}
		
		drawText(Centered, 3, "Target Game!", EightBit, White);
		drawNumber(5, 5, score, EightBit, Red);
		drawNumber(5, 15, bestHit, EightBit, Orange);
		render(true);
	}
}