#include "Camera.hpp"

Camera::Camera(Entity* entity_to_follow) : _entity_to_follow(entity_to_follow)
{
}

v2i Camera::get_top_left(int screen_w, int screen_h) // gets the top left world position
{
    v2f entity_loc = _entity_to_follow->_pos;

    v2i entity_size = { _entity_to_follow->get_entity_w(), _entity_to_follow->get_entity_h() };
    
    v2i screen_size = { screen_w, screen_h };

    // this is the world position 
    v2f pos_to_center = entity_loc + ((v2f)entity_size / 2.0f);
    v2f top_left = pos_to_center - ((v2f)screen_size / 2.0f);

    if (top_left.x < 0) top_left.x--;
    if (top_left.y < 0) top_left.y--;
    //return pos_to_center;
    return top_left;
}

v2i Camera::w_to_screen(v2f pos_in_world, int screen_w, int screen_h)
{
    v2f entity_loc = _entity_to_follow->_pos;
    v2i entity_size = { _entity_to_follow->get_entity_w(), _entity_to_follow->get_entity_h() };
    v2i screen_size = { screen_w, screen_h };

    // this is the world position 
    v2f cam_top_left = entity_loc + ((v2f)entity_size / 2.0f) - ((v2f)screen_size / 2.0f);
    v2f adjusted_pos = pos_in_world - cam_top_left;
    
    return (v2i)adjusted_pos;
}
