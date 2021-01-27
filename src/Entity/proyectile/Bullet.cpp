#include "Bullet.h"
#include "../../Utils/generalUtils.h"

Bullet::Bullet(const sf::Vector2f &speed, const sf::Vector2f &pos) :
	Projectile(pos, "bullet", 50.f)
{
	m_sprite.setTexture(m_textures[utils::randf() > 0.5f ? 1 : 2], true);
	SetSpeed(speed);
	if (m_speed.x > 0) { 
		m_dir = 1.f;
		utils::flipTexture(m_dir, m_scale, m_sprite);
		m_sprite.move(16, 0);
	}
}

void Bullet::ApplyResponse (const sf::Vector2f & vec) {
	m_sprite.move(vec);
	
	impacted = true;
	impact_life.restart();
}

void Bullet::Update ( ) 
{
	m_sprite.move(m_speed);
	if (impacted && impact_life.getElapsedTime().asSeconds() < 0.5f)
		in_use = false;
}

void Bullet::Render () {
	if (impacted) {
		m_sprite.setTexture(m_textures[utils::randf() > 0.5f ? 1 : 2], true);
		utils::flipTexture(-m_dir, m_scale, m_sprite);
	} else Projectile::Render();
	
	if (first) {
		first = !first;
		m_sprite.setTexture(m_textures[0], true);
	}
}

