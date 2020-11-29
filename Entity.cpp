#include "Entity.h"

Entity::Entity(std::string spritename, float initial_x, float initial_y) : 
	m_spritename(spritename), m_speed(0, 0)
{
	m_texture.loadFromFile(m_spritename);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(initial_x, initial_y);
}

