#include "GameState.h"

//void GameState::menuStateActions()
//{
//	md.menuCalculations(surface);
//		
//	if (key(Enter).pressed || key(Spacebar).pressed)
//			sd.startFade();
//	
//	if (sd.fadeEnd)
//	{
//		state = md.selectedOption + 1;
//		sd.startReverseFade();
//	}
//}

//void GameState::gameStateActions()
//{
//	//gameCalculations(&gd);
//}

//void GameState::runStateActions()
//{
//	switch (state)
//	{
//	case MENU_STATE: menuStateActions(); break;
//	case GAME_STATE: gameStateActions(); break;
//	//case OPTIONS_STATE: sysDrawText(40, 40, surface, "OPTIONS", EightBit, Default, Yellow); break;
//	//case CREDITS_STATE: sysDrawText(40, 40, surface, "CREDS", EightBit, Default, Yellow); break;
//	case EXIT_STATE: stopLoop();
//	}
//}

void GameState::startLoop() 
{
	runLoop = true;
}
void GameState::stopLoop()
{
	runLoop = false;
}
bool GameState::getLoop()
{
	return runLoop;
}

GameState::GameState()
{
	//md = MenuData();
	sd = ScreenData(surface);
	//gd = initalizeGame();
}