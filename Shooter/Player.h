#pragma once
#include "Entity.h"

#define RADIUS 5

class Player : public Entity
{
public:
	Player();
	void draw() override;
	void update() override;
};

