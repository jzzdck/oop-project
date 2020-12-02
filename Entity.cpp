#include "Entity.h"

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}

