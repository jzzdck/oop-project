#include "Revolver.h"
#include <iostream>
#include "../../../Bullet.h"

Revolver::Revolver(sf::Vector2f pos, bool facing, float wdt) : 
	Weapon(pos, "revolver", 30, facing, wdt), is_shooting(false)
{ m_sprite.scale(2,2); }

void Revolver::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[m_current]);
	win.draw(m_sprite);
}

Projectile * Revolver::GetProjectile ( ) {
	auto pos = m_sprite.getPosition();
	float dir = m_current ? -1.f : 1.f;
	pos.y += 3;
	return new Bullet(dir*15, pos);
}

bool Revolver::IsAttacking ( ) {
	if (is_shooting != attack_state) {
		is_shooting = !is_shooting;
		return is_shooting;
	}
	
	return false;
}

