#include "Revolver.h"
#include <iostream>
#include "../../proyectile/Bullet.h"
#include "../../../Utils/generalUtils.h"

Revolver::Revolver(sf::Vector2f pos, float facing) : 
	Weapon(pos, "revolver", facing, 6), is_shooting(false)
{ }

Projectile * Revolver::GetProjectile ( ) {
	auto pos = m_sprite.getGlobalBounds();
	auto pos2 = m_sprite.getLocalBounds();
	
	float add = m_dir == 1.f ? 0.f : pos2.width;
	return new Bullet({ m_dir*20, 0 } , {pos.left - add, pos.top});
}

bool Revolver::IsAttacking ( ) {
	if (is_shooting != attack_state) {
		is_shooting = !is_shooting;
		if (is_shooting) --m_ammo.current;
		return is_shooting && m_ammo.current >= 0;
	}
	
	return false;
}

