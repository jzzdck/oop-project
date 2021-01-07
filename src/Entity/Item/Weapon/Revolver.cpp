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
	pos.x += 50;
	return new Bullet(10, pos);
}

