#include "Bomb.h"

Bomb::Bomb(const sf::Vector2f &vel, const sf::Vector2f &pos) :
	Projectile(pos, "bomb")
{
	m_sprite.scale(4, 4);
	m_speed = vel;
}

void Bomb::ApplyResponse (const sf::Vector2f & vec) {
	if (exploding) return;
	m_sprite.move(vec);
	
	if (vec.x) m_speed = { -1.f*m_speed.x, m_speed.y };
	else if (vec.y) m_speed = { m_speed.x, -1.f*m_speed.y };
}

void Bomb::ApplyEffect (Player * target) {
	if (!exploding) return;
	
	Projectile::ApplyEffect(target);
}

void Bomb::Update ( ) {
	if (!exploding) {
		m_sprite.move(m_speed);
		if (timer.getElapsedTime().asSeconds() > 1.2f) {
			m_sprite.setTexture(m_textures[1], true);
			m_sprite.scale(2, 2);
			exploding = true;
			lifetime.restart();
		}
	} else if (lifetime.getElapsedTime().asSeconds() > 0.25f)
		in_use = false;
}

void Bomb::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

