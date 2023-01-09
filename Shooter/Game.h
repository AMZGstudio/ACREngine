#pragma once
#include "State.h"

#include "Bullet.h"
#include "Player.h"
#include "Zombie.h"

class Game : public State
{
private:
	Player p;
	std::vector<Bullet> bullets;
	std::vector<Zombie> zombies;

public:
	Game();
	int runState() override;
};

