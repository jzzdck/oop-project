#include "Bomb.h"
#include "../../Utils/generalUtils.h"

Bomb::Bomb(const sf::Vector2f &vel, const sf::Rect<float> &rect, float facing) :
	Projectile(rect, "bomb", rand()%(500-400) + 2, facing, 0.1f), 
	m_trail(m_sprite, false, 2.0f),
	explosion({nullptr, &m_sprite, "explosion", {8, 0, 0.05f, {40.f, 40.f}}})
{
	m_dir = facing;
	m_speed = vel;
	
	sf::Color trail_color = { 235, 106, 55, 125 };
	m_trail.SetColor(trail_color);
	m_trail.SetLength(14);
}

void Bomb::ApplyResponse (const sf::Vector2f & vec) {
	if (exploding) return;
	m_sprite.move(vec);
	
	if (vec.x) {
		m_speed = { -1.f*m_speed.x, m_speed.y }; 
		m_dir = m_speed.x < 0.f ? -1.f : 1.f;
	} else if (vec.y) 
		m_speed = { m_speed.x, -1.f*m_speed.y };
}

void Bomb::ApplyEffect (Player * target) {
	if (!exploding) { max_life = 0.1f; return; }
	HealthData &h = target->GetHealthData();
	h.current_health -= m_damage;
}

void Bomb::Update ( ) {
	if (!exploding) {
		if (timer.getElapsedTime().asSeconds() > max_life)
			Explode();
		else {
			m_accel.y += -m_speed.y * 0.04f;
			m_accel.x += -m_speed.x * 0.004f;
			Entity::Update();
			m_trail.AddPosition(GetBounds(), utils::getCenter(m_sprite.getLocalBounds()));
		}
	} else {
		m_trail.Pop();
		
		explosion.Update();
		if (explosion.IsFinished())
			in_use = false;
	}
}

void Bomb::Explode ( ) {
	m_sprite.setPosition(utils::getCenter(m_sprite.getGlobalBounds()));
	explosion.Update();
	m_sprite.setOrigin(utils::getCenter(m_sprite.getLocalBounds()));
	exploding = true;
	lifetime.restart();
}

void Bomb::Render (DrawingEnviroment &drawEnv) {
	m_sprite.setScale(m_dir*m_scale*2.f, m_scale*2.f);
	m_trail.Render(drawEnv); 
}

void Bomb::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_trail);
	target.draw(m_sprite);
}

sf::Vector2f Bomb::GetPushbackForce ( ) {
	return {m_dir*15, -5};
}

