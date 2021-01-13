#include "Handcannon.h"
#include <algorithm>
#include <iostream>
#include "../../proyectile/Bomb.h"
#include <cmath>

Handcannon::Handcannon(sf::Vector2f pos, bool facing) :
	Weapon(pos, "handcannon", 30, !facing, 20)
{
	m_sprite.scale(2,2);
	
	m_sprite.setTexture(m_textures[!m_current]);
}

void Handcannon::Draw(sf::RenderWindow & win) {
	float dir = m_current ? 1.f : -1.f;
	
	m_sprite.setRotation(dir*m_angle*180.f/M_PI);
	m_sprite.setScale(-dir*2, 2);
	if (Owner() != -1 && m_current)
		m_sprite.move(m_sprite.getGlobalBounds().width, 0);
	
	win.draw(m_sprite);
}

bool Handcannon::IsAttacking ( ) {
	if (m_nextangle) m_angle = m_nextangle = 0;
	
	if (attack_state)
		m_angle += 0.025, m_angle = std::min(m_angle, float(M_PI)/2.f);
	
	if (attack_state != is_shooting) {
		is_shooting = !is_shooting;
		bool can_shoot = firerate.getElapsedTime().asSeconds() > 0.5f;
		if (!is_shooting && can_shoot) 
			m_nextangle = m_angle, firerate.restart();
		
		return !is_shooting && can_shoot;
	} else return false;
}

Projectile * Handcannon::GetProjectile ( ) {
	float dir = m_current ? -1.f : 1.f;
	auto globals = m_sprite.getGlobalBounds();
	
	sf::Vector2f pos = { 
		globals.left + globals.width * (dir == 1.f ? .5f : 1.f),
		globals.top + 4
	};
	
	return new Bomb({ 
		m_current ? -1.f : 1.f *15*std::cos(m_angle), 
		-20*std::sin(m_angle)
	}, pos);
}

