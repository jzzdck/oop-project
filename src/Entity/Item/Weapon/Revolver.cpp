#include "Revolver.h"
#include <iostream>
#include "../../../Utils/generalUtils.h"

Revolver::Revolver(sf::Vector2f pos, float facing) : 
	Weapon(pos, "revolver", facing, 6), is_shooting(false)
{
	pushback = { 1, -1 };
	projectile_index = 1;
}

bool Revolver::IsAttacking ( ) {
	if (is_shooting != attack_state) {
		is_shooting = !is_shooting;
		if (is_shooting) --m_ammo.current;
		return is_shooting && m_ammo.current >= 0;
	}
	
	return false;
}

