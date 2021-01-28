#include "TeslaGun.h"
#include "ElectricShot.h"

TeslaGun::TeslaGun(const sf::Vector2f &pos, float facing) : 
	Weapon(pos, "teslagun", 1.f, 50) 
{
	m_ammo.current = 1;
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

Projectile * TeslaGun::GetProjectile ( ) {
	auto rect = m_sprite.getGlobalBounds();
	float x, y;
	
	y = rect.top - rect.height/2.f;
	x = rect.left + rect.width;
	
	return new ElectricShot(rect, {x, y}, m_dir);
}

