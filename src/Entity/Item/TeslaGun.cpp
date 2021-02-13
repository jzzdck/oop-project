#include "TeslaGun.h"

TeslaGun::TeslaGun(const sf::Vector2f &pos, float facing) : 
	Weapon(pos, "teslagun", 1.f, 50) 
{
	recoil = { 12, -3 }; 
	m_ammo.current = 1;
	projectile_index = 3;
}

bool TeslaGun::IsAttacking ( ) {
	if (attack_state && not shot)
		m_ammo.current++;
	else if (not shot && m_ammo.current > 0)
		m_ammo.current--;
	
	if (m_ammo.current >= m_ammo.max) {
		m_ammo.current = -1000;
		shot = true;
		return shot;
	} else return false;
}

