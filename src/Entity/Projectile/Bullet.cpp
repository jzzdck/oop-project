#include "Bullet.h"
#include "../../Utils/generalUtils.h"
#include <cmath>

Bullet::Bullet(const sf::Vector2f &speed, const sf::Rect<float> &rect, float facing) :
	Projectile(rect, "bullet", rand()%(125-50) + 50, facing, 0.40f)
{
	m_speed = speed;
	float angle = std::atan2(m_speed.y, m_speed.x) * 180.f / M_PI;
	m_sprite.move(0, -5);
	ray.setScale(-m_dir, 1.f);
	pos = m_sprite.getPosition();
	ray.setPosition(m_sprite.getPosition());
	ray.setSize({m_dir*30, m_sprite.getGlobalBounds().height});
	ray.setRotation(angle);
	m_sprite.setRotation(angle);
}

void Bullet::ApplyResponse (const sf::Vector2f & vec) {
	if (vec.x) m_sprite.move(vec);
	
	impacted = true;
	impact_life.restart();
}

void Bullet::Update ( ) {
	if (!impacted) {
		ray_width = std::fabs(m_sprite.getPosition().x - pos.x); 
		m_sprite.move(m_speed);
	} else {
		auto dim = ray.getGlobalBounds();
		sf::Uint8 alpha(ray.getFillColor().a * 0.95f + sf::Color::Transparent.a * 0.05f);
		ray.setFillColor({250, 250, 250, alpha});
		m_sprite.setColor({250, 250, 250, alpha});
	}
	
	ray.setPosition(m_sprite.getPosition());
	ray.setSize({m_dir*ray_width, m_sprite.getGlobalBounds().height});
	if (m_sprite.getColor().a < 20)
		in_use = false;
}

sf::Vector2f Bullet::GetPushbackForce ( ) {
	return {m_dir*2, -2};
}

void Bullet::Render (DrawingEnviroment & drawEnv) {
	Projectile::Render();
	drawEnv.AddToLayer(&ray, 0);
}

void Bullet::ApplyEffect (Player * target) {
	if (impacted) return;
	HealthData &h = target->GetHealthData();
	h.current_health -= m_damage * (utils::randf() < crit_chance ? 1.5f : 1.f);
	impacted = true;
}

