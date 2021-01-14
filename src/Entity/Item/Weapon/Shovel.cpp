#include "Shovel.h"
#include "../../../MeleeHit.h"
#include "../../../Utils/generalUtils.h"

Shovel::Shovel(sf::Vector2f pos) : Weapon(pos, "shovel", true, 0) 
{
}

Projectile * Shovel::GetProjectile ( ) {
	auto pos = m_sprite.getGlobalBounds();
	auto pos2 = m_sprite.getLocalBounds();
	pos.left += 70*m_dir;
	float add = m_dir == 1.f ? 0.f : pos2.width;
	
	return new MeleeHit({pos.left - add, pos.top});
}

bool Shovel::IsAttacking ( ) {
	if (is_attacking != attack_state) {
		is_attacking = !is_attacking;
		return is_attacking;
	}
	
	return false;
}

