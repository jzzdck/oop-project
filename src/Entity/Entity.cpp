#include "Entity.h"
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"

Entity::Entity (sf::Vector2f pos, std::string keyword) : 
	m_key(keyword), m_initpos(pos)
{
	FileManager s("textures.conf", m_key);
	int psize = std::stoi(s[m_key+"-size"]);
	
	m_textures.resize(psize);
	for (size_t i=0; i<m_textures.size(); ++i)
		m_textures[i].loadFromFile(s[m_key+"-texture"+std::to_string(i)] + ".png");
	if (psize) m_sprite.setTexture(m_textures[0]);
	
	m_sprite.setPosition(m_initpos);
	m_sprite.setScale(m_dir*m_scale, m_scale);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}


bool Entity::CollidesWith(Entity *another) {
	return this->GetBounds().intersects(another->GetBounds());
}

void Entity::ApplyResponse (const sf::Vector2f & vec) {
	m_sprite.move(vec.x, vec.y);
	if (!vec.x) m_speed.y = 0;
}

