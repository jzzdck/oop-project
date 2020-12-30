#include "Entity.h"
#include "FileManager.h"

Entity::Entity (sf::Vector2f pos, std::string keyword) : m_key(keyword) {
	FileManager s("textures.conf", m_key);
	int psize = std::stoi(s[m_key+"-size"]);
	
	m_textures.resize(psize);
	for (size_t i=0; i<m_textures.size(); ++i)
		m_textures[i].loadFromFile(s[m_key+"-texture"+std::to_string(i)] + ".png");
	if (psize) m_sprite.setTexture(m_textures[0]);
	
	m_sprite.setPosition(pos.x, pos.y);
}

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}

void Entity::Update ( ) { 
	m_sprite.move(m_speed.x, m_speed.y); 
};

void Entity::ApplyResponse (const sf::Vector2<double> & vec) {
	m_sprite.move(vec.x, vec.y);
	if (!vec.x) m_speed.y = 0;
}

