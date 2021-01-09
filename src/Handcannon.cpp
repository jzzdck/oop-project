#include "Handcannon.h"
#include "Bomb.h"
#include <algorithm>
#include <iostream>

Handcannon::Handcannon(sf::Vector2f pos, bool facing) :
	Weapon(pos, "handcannon", 30, !facing, 20)
{
	m_sprite.scale(2,2);
}

void Handcannon::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[!m_current]);
	win.draw(m_sprite);
}

bool Handcannon::IsAttacking ( ) {
	if (m_nextspeed) m_bombspeed = m_nextspeed = 0;
	
	if (attack_state) {
		m_bombspeed += 0.55;
		m_bombspeed = std::min(m_bombspeed, 35.f);
	}
	
	std::cout << "updated b" << m_bombspeed << std::endl;
	if (attack_state != is_shooting) {
		is_shooting = !is_shooting;
		if (!is_shooting) m_nextspeed = m_bombspeed;
		return !is_shooting;
	} else return false;
}

Projectile * Handcannon::GetProjectile ( ) {
	float dir = m_current ? -1.f : 1;
	
	return new Bomb({dir*12, -m_bombspeed}, m_sprite.getPosition());
}

