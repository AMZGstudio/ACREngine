#pragma once

#include "Types.hpp"
#include "Entity.hpp"
#include "../acre files/ACREngine.h"

class Camera
{
public:
	Entity* _entity_to_follow;

	Camera(Entity* entity_to_follow);
	v2i get_top_left(int screen_w, int screen_h);
	v2i w_to_screen(v2f world_pos, int screen_w, int screen_h);

private:

};

