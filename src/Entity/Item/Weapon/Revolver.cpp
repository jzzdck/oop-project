#include "Revolver.h"
#include <iostream>
#include "../../../Bullet.h"

Revolver::Revolver(sf::Vector2f pos, bool facing, float wdt) : 
	Weapon(pos, "revolver", 30, facing, wdt)
{ m_sprite.scale(2,2); }

void Revolver::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[m_current]);
	win.draw(m_sprite);
}

Projectile * Revolver::GetProjectile ( ) {
	auto pos = m_sprite.getPosition();
	float dir = m_current ? -1.f : 1.f;
	pos.x += 60*dir;
	return new Bullet(dir*50, pos);
}

