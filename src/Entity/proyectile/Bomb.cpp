#include "Bomb.h"

Bomb::Bomb(const sf::Vector2f &vel, const sf::Vector2f &pos) :
	Projectile(pos, "bomb", 50.f), m_trail(m_sprite, false, 2.0f)
{
	m_scale *= 2;
	m_sprite.scale(m_scale, m_scale);
	m_speed = vel;
}

void Bomb::ApplyResponse (const sf::Vector2f & vec) {
	if (exploding) return;
	m_sprite.move(vec);
	
	if (vec.x) m_speed = { -1.f*m_speed.x, m_speed.y };
	else if (vec.y) m_speed = { m_speed.x, -1.f*m_speed.y };
}

void Bomb::ApplyEffect (Player * target) {
	if (!exploding) { max_life = 0.1f; return; }
	target->AssignHealth(target->GetHealth() - m_damage);
}

void Bomb::Update ( ) {
	if (!exploding) {
		m_sprite.move(m_speed);
		if (timer.getElapsedTime().asSeconds() > max_life)
			Explode();
	} else if (lifetime.getElapsedTime().asSeconds() > 0.25f)
		in_use = false;
	
	m_trail.AddPosition(m_sprite.getPosition());
}

void Bomb::Explode ( ) {
	m_sprite.setTexture(m_textures[1], true);
	exploding = true;
	lifetime.restart();
}

void Bomb::Render (DrawingEnviroment &drawEnv) {
	utils::flipTexture(m_dir, m_scale, m_sprite);
	m_trail.Render(drawEnv); 
}

void Bomb::ApplyGravity (float gravity) {
	m_speed.y += gravity*0.75;
}

void Bomb::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_trail);
	target.draw(m_sprite);
}

