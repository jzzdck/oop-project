#include "Handcannon.h"
#include <algorithm>
#include <iostream>
#include "../../proyectile/Bomb.h"
#include <cmath>
#include "../../../Utils/generalUtils.h"

Handcannon::Handcannon(sf::Vector2f pos, float facing) :
	Weapon(pos, "handcannon", facing, 2)
{
}

void Handcannon::Draw(sf::RenderWindow & win) {
	win.draw(m_sprite);
}

bool Handcannon::IsAttacking ( ) {
	if (m_nextangle) m_angle = m_nextangle = 0;
	
	if (attack_state)
		m_angle += 0.025, m_angle = std::min(m_angle, float(M_PI)/2.f);
	
	if (attack_state != is_shooting) {
		is_shooting = !is_shooting;
		bool can_shoot = firerate.getElapsedTime().asSeconds() > 0.5f;
		if (!is_shooting && can_shoot && m_ammo >= 0) 
			m_nextangle = m_angle, firerate.restart(), --m_ammo;
		else
			m_angle = 0;
		
		return !is_shooting && can_shoot && m_ammo >= 0;
	} else return false;
}

Projectile * Handcannon::GetProjectile ( ) {
	auto globals = m_sprite.getGlobalBounds();
	
	sf::Vector2f pos = { 
		globals.left + globals.width * (m_dir == -1.f ? 1.5f : 1.f),
		globals.top + 4
	};
	
	return new Bomb(
		{m_dir * 20.f * std::cos(m_angle), -20.f * std::sin(m_angle)}, 
		pos
	);
}

void Handcannon::Update ( ) {
	Weapon::Update();
	utils::flipTexture(m_dir, m_scale, m_sprite),
	m_sprite.setRotation(-m_dir*m_angle*180.f/M_PI);
	
	if (m_dir == -1.f && Owner() != -1)
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width/2.f, 0);
}


