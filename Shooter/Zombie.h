#pragma once
#include "Entity.h"
#include "Player.h"

#define RADIUS 5

class Zombie : public Entity
{
private:
	Player& player;

public:
	Zombie(Player& p);
	Zombie(const Zombie& other);

	Zombie& operator=(const Zombie& other);

	void update() override;
	void draw() override;

	float getRadius();
	bool pointCollide(int x, int y);	
};

