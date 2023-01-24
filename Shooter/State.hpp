#pragma once
#include <vector>
#include <string>
#include <map>

#include "../ACRE Files/ACREngine.h"

//enum all_states { menu, game, over };

class State
{
public:
	virtual void runState(std::string& state) = 0;
};

class States
{
private:
	// vector of functions
	std::map<std::string, State*> states;
	Area surface;
	std::string currState;

public:
	std::map<std::string, int> leaderboard;

	States(std::string stateName);
	void runState();
	void setState(std::string name);
	void addState(std::string name, State* state);
	Area& getArea();
};