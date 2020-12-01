#include "Entity.h"

Entity::Entity(std::string spritename, float initial_x, float initial_y) : 
	m_spritename(spritename), m_speed(0, 0)
{
	m_textures.resize(1);
	m_textures[0].loadFromFile(m_spritename);
	m_sprite.setTexture(m_textures[0]);
	m_sprite.setPosition(initial_x, initial_y);
}

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}

