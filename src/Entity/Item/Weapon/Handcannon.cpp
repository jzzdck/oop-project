#include "Handcannon.h"
#include <algorithm>
#include <iostream>
#include "../../proyectile/Bomb.h"
#include <cmath>

Handcannon::Handcannon(sf::Vector2f pos, bool facing) :
	Weapon(pos, "handcannon", 30, !facing, 20)
{
	m_sprite.scale(2,2);
}

void Handcannon::Draw(sf::RenderWindow & win) {
	auto dim = m_sprite.getLocalBounds();
	float dir = 1.f;
	
	m_sprite.setTexture(m_textures[!m_current]);
	if (!m_current) dir = -1.f, dim.width = 0;
	m_sprite.rotate(dir*float(m_angle*180/M_PI));
	m_sprite.setOrigin(dim.width, dim.height);
	
	if (Owner() != -1) 
		m_sprite.move(dim.width, dim.height);
	win.draw(m_sprite);
	
	m_sprite.setRotation(0);
}

bool Handcannon::IsAttacking ( ) {
	if (m_nextangle) m_angle = m_nextangle = 0;
	
	if (attack_state) {
		m_angle += 0.025;
		m_angle = std::min(m_angle, float(M_PI/2.f));
	}
	
	if (attack_state != is_shooting) {
		is_shooting = !is_shooting;
		bool can_shoot = firerate.getElapsedTime().asSeconds() > 0.5f;
		if (!is_shooting && can_shoot) { 
			m_nextangle = m_angle;
			firerate.restart();
		}
		
		return !is_shooting && can_shoot;
	} else return false;
}

Projectile * Handcannon::GetProjectile ( ) {
	float dir = m_current ? -1.f : 1;
	auto pos = m_sprite.getPosition();
	pos.x += dir*20;
	
	return new Bomb({dir*15*std::cos(m_angle), -20*std::sin(m_angle)}, pos);
}

