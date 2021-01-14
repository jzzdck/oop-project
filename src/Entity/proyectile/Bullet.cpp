#include "Bullet.h"
#include "../../Utils/phutils.h"

Bullet::Bullet(const sf::Vector2f &speed, const sf::Vector2f &pos) :
	Projectile(pos, "bullet")
{
	SetSpeed(speed);
	if (m_speed.x > 0) { 
		m_dir = 1.f;
		utils::flipTexture(m_dir, m_scale, m_sprite);
		m_sprite.move(16, 0);
	}
}

void Bullet::ApplyResponse (const sf::Vector2f & vec) {
	in_use = false;
}

void Bullet::Update ( ) {
	m_sprite.move(m_speed);
}
