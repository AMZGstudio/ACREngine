#pragma once
#include <vector>

#include "Entity.h"
#include "Zombie.h"

class Bullet : public Entity
{
private:
	static constexpr float _vel = 60;

public:
	Bullet(int px, int py, int mx, int my);
	
	void draw() override;
	void update() override;

	bool damageOther(std::vector<Zombie>& z, float hitAmount);
};

