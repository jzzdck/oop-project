#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, 
			   int damage, float facing) :
	Item(pos, keyword), 
	m_damage(damage),
	attack_state(false)
{
	m_dir = facing;
}

sf::Vector2f Weapon::OffSet(const sf::Rect<float> &to_offset) {
	auto dim = m_sprite.getGlobalBounds();
	float x = to_offset.left - dim.width/2.f;
	float y = to_offset.top + to_offset.height/3.f;
	if (m_dir == 1.f)
		x += to_offset.width;
	
	return sf::Vector2f(x, y);
}

void Weapon::SetPos(const sf::Rect<float> & relative_to, float facing) {
	m_dir = facing;
	m_pos = OffSet(relative_to);
	m_sprite.setPosition(m_pos);
}
