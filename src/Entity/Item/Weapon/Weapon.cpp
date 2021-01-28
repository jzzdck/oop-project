#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count) :
	Item(pos, keyword), 
	attack_state(false),
	m_ammo(ammo_count)
{
	max_ammo = m_ammo;
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

void Weapon::Update ( ) {
	Item::Update();
	
	if (m_speed.x == 0 && m_speed.y == 0 && m_ammo < 0)
		in_use = false;
}
