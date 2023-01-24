//#define ACRE_START
//#define SHOW_FPS
//#include "../ACRE Files/ACREngine.h"
//
//#include <vector>
//
//using std::vector;
//
//
//
//
//class Objects
//{
//public:
//	float x, y, speed, moving = false, stopped = false, Acreated = false;
//
//	void startObject()
//	{
//		x = Width(Screen) / 2, y = Height(Screen) / 2, speed = 100;
//	}
//
//	void updateObject(int type)
//	{
//		if (type == 1) //Target
//		{
//			if (key(Spacebar).pressed && !stopped)
//			{
//				moving = !moving;
//				if (!moving) stopped = true;
//			}
//			if (moving) x += timePerSec(speed);
//			if (x >= Width(Screen)) x = 0;
//		}
//
//		if (type == 2) //Arrow
//		{
//			if (key(Spacebar).pressed && !stopped)
//			{
//				moving = !moving;
//				if (!moving) stopped = true;
//
//			}
//			if (moving) x -= timePerSec(speed / 2);
//			if (x <= 0) x = Width(Screen);
//		}
//	}
//
//
//	void drawObject(int type) //type number will refer to which object it will be
//	{
//		if (type == 1) //Target
//		{
//			drawCircleFilled(x, y, 6, Red);
//			drawCircle(x, y, 3, White);
//			drawCircle(x, y, 5, White);
//			drawCircle(x, y, 1, White);
//		}
//
//		if (type == 2) //Arrow
//		{
//			drawCircle(x, y, 1, Grey);
//			drawPixel(x, y, Brown);
//		}
//
//	}
//
//};
//
//
//
//
//int main()
//{
//	initalize("Target Game", 250, 125, 3, 3, Default, Default);
//
//	vector<Objects> TnA;
//
//
//
//	int score = 0;
//	int scoreUp = 0;
//	int bestHit = 0;
//	bool scored = false;
//	int scorer = 0;
//	int scoreEffect = -10;
//	int effectMod = -1;
//	bool startRound = true;
//	bool clearRound = true;
//
//
//	while (!key(Esc).pressed)
//	{
//		if (startRound)
//		{
//			TnA.push_back(Objects());
//			TnA[0].startObject();
//			scoreUp = 0;
//			scored = false;
//			scorer = 0;
//			scoreEffect = -10;
//			effectMod = -1;
//			startRound = false;
//		}
//
//
//
//		if (!TnA[0].stopped)
//		{
//			TnA[0].updateObject(1);
//		}
//		if (TnA[0].stopped)
//		{
//			if (!TnA[0].Acreated)
//			{
//				TnA.push_back(Objects());
//				TnA[0].Acreated = true;
//				TnA[1].startObject();
//			}
//
//			TnA[1].updateObject(2);
//
//		}
//
//		TnA[0].drawObject(1);
//		if (TnA[0].Acreated)
//		{
//			TnA[1].drawObject(2);
//			if (TnA[1].stopped && !scored)
//			{
//				if (abs(TnA[1].x - TnA[0].x) <= 7)
//				{
//					scoreUp += 7 - abs(TnA[1].x - TnA[0].x);
//					score += scoreUp;
//					if (bestHit < scoreUp) bestHit = scoreUp;
//
//				}
//
//				scored = !scored;
//			}
//
//			if (TnA[1].stopped)
//			{
//				while (scorer < 15)
//				{
//
//					drawNumber((TnA[0].x), Height(Screen) / 2 + scoreEffect, scoreUp, EightBit, Green);
//					scoreEffect -= 1;
//					scorer += 1;
//
//					render(true);
//
//				}
//
//				scoreEffect = 0;
//				TnA.clear();
//				startRound = true;
//			}
//			/*for (clearRound = false; clearRound = true; )
//			{
//				if (key(Spacebar).pressed)
//				{
//					clearRound = true;
//					scoreEffect = 0;
//					TnA.clear();
//					startRound = true;
//				}
//
//			}*/
//
//		}
//
//
//
//
//
//
//
//
//		drawNumber(5, 5, score, EightBit, Red);
//
//		drawNumber(5, 15, bestHit, EightBit, Orange);
//
//		render(true);
//	}
//
//
//
//
//}