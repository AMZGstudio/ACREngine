#pragma once
#include "Entity.hpp"
#include "Player.hpp"

#include <vector>
#define RADIUS 5

class Wave
{
public:
	static bool waveStarted;
	static int waveNum;
	static int amountSpawned;
	static float timeFromSpawned;

public:
	static bool nextWave();
	static bool spawnZombie();
	static int getNumEntities();

	static void reset();
};

class Zombie : public Entity
{
private:
	Player& _player;
	std::vector<Zombie>& _zombies;
	float _speed;

public:
	Zombie(Player& p, std::vector<Zombie>& zombies, float speed);
	Zombie(const Zombie& other);

	Zombie& operator=(const Zombie& other);
	bool operator==(const Zombie& rhs);

	void update() override;
	void draw() override;
	bool zombieCollide() const;
	bool playerCollide() const;

	float getRadius();
};

