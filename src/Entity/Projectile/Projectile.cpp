#include "Projectile.h"
#include <iostream>

Projectile::Projectile(const sf::Rect<float> &rect, std::string keyword, float damage, float facing, float crit_chance) : 
	Entity({0, 0}, keyword), m_damage(damage), crit_chance(crit_chance)
{ 
	m_dir = facing;
	
	// projectiles are set relative to weapons, at half their height and furthest point to the right
	auto globals = m_sprite.getGlobalBounds();
	m_sprite.setPosition(rect.left + rect.width, rect.top + rect.height/2.f);
	m_sprite.move(0, -globals.height/2.f);
	
	if (m_dir == -1.f)
		m_sprite.move(- rect.width - globals.width, 0);
}

void Projectile::ApplyEffect (Player * target) {
	HealthData &h = target->GetHealthData();
	h.current_health -= m_damage * (utils::randf() < crit_chance ? 1.5f : 1.f);
	in_use = false;
}
