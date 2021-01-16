#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, std::string keyword, float damage) : 
	Entity(pos, keyword), m_damage(damage)
{ }

void Projectile::ApplyEffect (Player * target) {
	target->AssignHealth(target->GetHealth() - m_damage);
	in_use = false;
}

