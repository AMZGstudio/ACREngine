#include "Entity.hpp"

Entity::Entity(v2f position, Side facing)
{
	bounding_box = { 0, 0, 0, 0 };
	this->facing = facing; 
	_pos.x = position.x;
	_pos.y = position.y;
}

void Entity::calculate_bb()
{
	Area ar = _texture[facing];
	int h = _texture[facing].h;
	int w = _texture[facing].w;

	bounding_box.yStart = 0;
	bounding_box.yEnd   = h;
	bounding_box.xStart = 0;
	bounding_box.xEnd   = w;

	bool p1HitX = false, p2HitX = false;

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
			if (sysGetBackColor(x, y, ar) != Default)
			{
				if (!p1HitX)
					p1HitX = true, bounding_box.xStart = x;

				if (y < bounding_box.yStart)
					bounding_box.yStart = y;
			}

	for (int x = w - 1; x >= 0; x--)
		for (int y = h - 1; y >= 0; y--)
			if (sysGetBackColor(x, y, ar) != Default)
			{
				if (!p2HitX)
					p2HitX = true, bounding_box.xEnd = x;
				if (y > bounding_box.yEnd)
					bounding_box.yEnd = y;
			}
}

void Entity::add_side(std::string path, Side side)
{
	_texture[side] = loadSprite(path.c_str());
	calculate_bb();
}

void Entity::set_facing(Side side)
{
	if (facing == side)
		return;

	if (_texture.contains(side))
	{
		facing = side;
		calculate_bb();
	}
}

void Entity::draw(v2i screen_position)
{
	drawArea(screen_position.x, screen_position.y, _texture[facing]);
}

int Entity::get_entity_w()
{
	return _texture[facing].w;
}

int Entity::get_entity_h()
{
	return _texture[facing].h;
}

Space Entity::get_bounding_box()
{
	return bounding_box;
}


