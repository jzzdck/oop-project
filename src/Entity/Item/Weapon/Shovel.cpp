#include "Shovel.h"
#include "../../../Utils/generalUtils.h"

Shovel::Shovel(sf::Vector2f pos) : Weapon(pos, "shovel", true, 0)
{
	recoil = {0, 0};
	projectile_index = 0;
}

bool Shovel::IsAttacking ( ) {
	if (is_attacking != attack_state) {
		is_attacking = !is_attacking;
		return is_attacking;
	}
	
	return false;
}

