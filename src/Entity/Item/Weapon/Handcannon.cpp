#include "Handcannon.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include "../../../Utils/generalUtils.h"

Handcannon::Handcannon(sf::Vector2f pos, float facing) :
	Weapon(pos, "handcannon", facing, 50)
{
	projectile_index = 2;
}

void Handcannon::Render(DrawingEnviroment &drawEnv) {
}

bool Handcannon::IsAttacking ( ) {
	if (m_nextangle) m_angle = m_nextangle = 0;
	
	if (attack_state)
		m_angle += 0.025, m_angle = std::min(m_angle, float(M_PI)/2.f);
	
	if (attack_state != is_shooting) {
		is_shooting = !is_shooting;
		bool can_shoot = firerate.getElapsedTime().asSeconds() > 0.5f && Owner() != -1;
		if (!is_shooting && can_shoot && m_ammo.current >= 0) 
			m_nextangle = m_angle, firerate.restart(), --m_ammo.current;
		else
			m_angle = 0;
		
		return !is_shooting && can_shoot && m_ammo.current >= 0;
	} else return false;
}

void Handcannon::Update ( ) {
	Weapon::Update();
	float angle = m_angle*180.f/M_PI;
	m_sprite.setRotation(-angle);
	
	if (m_dir == -1.f) {
		m_sprite.setRotation(180 + angle);
		m_sprite.setScale(m_scale, m_dir*m_scale);
	} else
		m_sprite.setScale(m_scale, m_scale);
	
	if (Owner() == -1)
		m_angle = m_nextangle = 0, is_shooting = false;
}

void Handcannon::SetPos (const sf::Rect<float> & relative_to, float facing) {
	m_dir = facing;
	m_sprite.setPosition({relative_to.left, relative_to.top+30});
	
	if (facing == -1.f)
		m_sprite.move(15, 0);
	else
		m_sprite.move(relative_to.width - 15, 0);
}

ProjectileData Handcannon::GetProjectileData ( ) {
	return { GetBounds(), projectile_index, GetFacing(), m_angle };
}

