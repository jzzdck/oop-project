#include "Entity.h"
#include "Settings.h"

Entity::Entity (std::string keyword) : m_key(keyword) {
	Settings s("textures.conf", m_key);
	int psize = std::stoi(s[m_key+"-size"]);
	
	m_textures.resize(psize);
	for (size_t i=0; i<m_textures.size(); ++i)
		m_textures[i].loadFromFile(s[m_key+"-texture"+std::to_string(i)] + ".png");
	
	if (psize) m_sprite.setTexture(m_textures[0]);
}

bool Entity::CollidesWith(const Entity & another) {
	return m_sprite.getGlobalBounds().intersects(another.m_sprite.getGlobalBounds());
}
