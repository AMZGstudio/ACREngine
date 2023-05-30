#pragma once

#include <string>
#include <map>
#include "../acre files/ACREngine.h"
#include "Types.hpp"

class Entity
{
public:
	enum Side {FrontSide, BackSide, LeftSide, RightSide};
private:
	std::map<Side, Area> _texture;
	Space bounding_box;

public:
	// this is the world position
	v2f _pos;
	Side facing;

	Entity(v2f position, Side facing);
	
	void calculate_bb();
	void add_side(std::string path, Side side);

	void set_facing(Side side);
	void draw(v2i screen_position);
	int get_entity_w();
	int get_entity_h();

	Space get_bounding_box();
};

