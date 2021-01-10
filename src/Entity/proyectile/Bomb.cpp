#include "Bomb.h"

Bomb::Bomb(const sf::Vector2f &vel, const sf::Vector2f &pos) :
	Projectile(pos, "bomb")
{
	m_sprite.scale(3,3);
	m_speed = vel;
}

void Bomb::ApplyResponse (const sf::Vector2f & vec) {
	m_sprite.move(vec);
	
	if (vec.x) m_speed = { -1.f*m_speed.x, m_speed.y };
	else if (vec.y) m_speed = { m_speed.x, -1.f*m_speed.y };
}

void Bomb::ApplyEffect (Player * target) {
	target->GetSprite().setPosition(target->GetInitPos());
	target->SetSpeed({0, 0});
	in_use = false;
}

void Bomb::Update ( ) {
	m_sprite.move(m_speed);
}

void Bomb::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

