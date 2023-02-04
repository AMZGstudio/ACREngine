#pragma once
#include <vector>

#include "Entity.hpp"
#include "Zombie.hpp"

#include "Audio.h"

class Bullet : public Entity
{
private:
	static constexpr float _vel = 60;

public:
	Bullet(int px, int py, float playerRadius, int mx, int my);
	
	void draw() override;
	void update() override;

	bool damageZombie(std::vector<Zombie>& z, float hitAmount);
	bool damagePlayer(Player& player, float hitAmount);
};

