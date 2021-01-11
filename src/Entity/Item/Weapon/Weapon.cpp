#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, 
			   int damage, bool facing, float width) :
	Item(pos, keyword), 
	m_damage(damage), 
	m_current(facing), 
	m_width(width), attack_state(false)
{
	
}

void Weapon::SetText() {
	m_sprite.setTexture(m_textures[m_current]);
}

sf::Vector2f Weapon::OffSet(const sf::Rect<float> &to_offset) {
	auto dim = m_sprite.getGlobalBounds();
	float x = to_offset.left - dim.width/2.f;
	float y = to_offset.top + to_offset.height/3.f;
	if (!m_current)
		x += to_offset.width;
	
	return sf::Vector2f(x, y);
}

void Weapon::SetPos(const sf::Rect<float> & relative_to, bool facing) {
	m_current = facing;
	m_pos = OffSet(relative_to);
	m_sprite.setPosition(m_pos);
}

