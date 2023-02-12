#pragma once

#include "../ACRE Files/ACREngine.h"

class Entity
{
protected:
	float x, y, vx, vy;
	float health;
	Entity(float health);
	Entity(const Entity& other);

	virtual void draw() = 0;
	virtual void update() = 0;

public:
	void hit(float amount);
	void kill();
	bool isAlive() const;

	float getX();
	float getY();
	float getVX();
	float getVY();
	float getHealth();
};

