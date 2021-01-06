#include "Entity.h"
#include "../FileManager.h"

Entity::Entity (sf::Vector2f pos, std::string keyword) : 
	m_key(keyword), is_alive(true)
{
	m_initpos = pos;
	FileManager s("textures.conf", m_key);
	int psize = std::stoi(s[m_key+"-size"]);
	
	m_textures.resize(psize);
	for (size_t i=0; i<m_textures.size(); ++i)
		m_textures[i].loadFromFile(s[m_key+"-texture"+std::to_string(i)] + ".png");
	if (psize) m_sprite.setTexture(m_textures[0]);
	
	m_sprite.setPosition(m_initpos);
}

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}

void Entity::ApplyResponse (const sf::Vector2f & vec) {
	m_sprite.move(vec.x, vec.y);
	if (!vec.x) m_speed.y = 0;
}
