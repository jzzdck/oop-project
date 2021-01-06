#include "Item.h"
#include <cmath>

Item::Item(sf::Vector2f pos, std::string keyword) 
	: Entity(pos, keyword), m_owner(-1) {}

void Item::Update ( ) {
	if (Owner() != -1) return;
	m_sprite.move(m_speed.x, m_speed.y);
	
	float fr = 0.25, dir = 1.f;
	
	if (m_speed.x < 0) {
		m_speed.x = std::fabs(m_speed.x);
		dir = -1.f;
	} 
	
	if (m_speed.x > 0) {
		if (m_speed.x - fr < 0) m_speed.x = 0;
		else m_speed.x -= fr;
	}
	
	m_speed.x *= dir;
}

