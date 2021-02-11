#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, float facing, int ammo_count) :
	Item(pos, keyword), 
	attack_state(false),
	m_ammo({ ammo_count, ammo_count })
{
	lifetime = sf::seconds(5.f);
	m_dir = facing;
}

void Weapon::Update ( ) {
	Item::Update();
	if (m_ammo.current < 0 && Owner() == -1)
		start_time = true; 
	
	if (start_time && clock.getElapsedTime() - released > lifetime)
		in_use = false;
	else if (!start_time)
		released = clock.getElapsedTime();
}

ProjectileData Weapon::GetProjectileData ( ) {
	sf::Vector2f aux = { -m_dir*pushback.x, pushback.y };
	return { GetBounds(), projectile_index, GetFacing(), 0, aux };
}
