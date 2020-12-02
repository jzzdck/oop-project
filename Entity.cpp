#include "Entity.h"

Entity::Entity(float initial_x, float initial_y) : m_speed(0, 0)
{

}

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}

