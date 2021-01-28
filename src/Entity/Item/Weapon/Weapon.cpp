#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count) :
	Item(pos, keyword), 
	attack_state(false),
	m_ammo({ ammo_count, ammo_count })
{
	m_dir = facing;
}

void Weapon::Update ( ) {
	Item::Update();
	
	if (m_speed.x == 0 && m_speed.y == 0 && m_ammo.current < 0)
		in_use = false;
}
