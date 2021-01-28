#include "Item.h"
#include <cmath>
#include "../../Utils/generalUtils.h"

Item::Item(sf::Vector2f pos, std::string keyword) 
	: Entity(pos, keyword), m_owner(-1) {}

void Item::Update ( ) {
	if (Owner() != -1) return;
	m_dir = m_speed.x > 0 ? 1.f : -1.f;
	
	if (m_platform) 
		m_sprite.move(m_platform->getSpeed());
	m_sprite.move(m_speed.x, m_speed.y);
	
	float fr = 0.25;
	
	if (m_speed.x < 0)
		m_speed.x = std::fabs(m_speed.x);
	
	if (m_speed.x > 0) {
		if (m_speed.x - fr < 0) m_speed.x = 0;
		else m_speed.x -= fr;
	}
	
	m_speed.x *= m_dir;
}

void Item::ApplyResponse (const sf::Vector2f & vec) {
	if (m_owner != -1) return; 
	else Entity::ApplyResponse(vec);
}

void Item::Draw (sf::RenderWindow & win) {
	m_sprite.setScale(m_dir*m_scale, m_scale);
	win.draw(m_sprite);
}

void Item::SetPos (const sf::Rect<float> & relative_to, float facing) {
	m_dir = facing;
	m_sprite.setPosition({relative_to.left, relative_to.top+30});
	
	if (facing == -1.f)
		m_sprite.move(15, 0);
	else
		m_sprite.move(relative_to.width - 15, 0);
}

