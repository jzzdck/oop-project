#include "Shovel.h"
#include "../../../Bullet.h"

Shovel::Shovel(sf::Vector2f pos) : Weapon(pos, "shovel", 90, true, 0) 
{
	m_sprite.scale(2,2);
}

void Shovel::Draw(sf::RenderWindow & win)
{
	win.draw(m_sprite);
}

Projectile * Shovel::GetProjectile ( ) {
	auto pos = m_sprite.getPosition();
	pos.x += 50;
	
	return new Bullet(10, pos);
}

