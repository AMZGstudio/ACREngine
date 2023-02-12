#pragma once
#include "Entity.hpp"

#define RADIUS 2

class Player : public Entity
{
public:
	Player();
	void draw() override;
	void update() override;

	float getRadius() const;
};

