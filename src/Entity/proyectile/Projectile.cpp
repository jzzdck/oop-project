#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, std::string keyword, float damage) : 
	Entity(pos, keyword), m_damage(damage)
{ }

void Projectile::ApplyEffect (Player * target) {
	HealthData &h = target->GetHealthData();
	h.current_health -= m_damage;
	in_use = false;
}

