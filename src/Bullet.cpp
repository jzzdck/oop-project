#include "Bullet.h"

Bullet::Bullet(float xspeed, const sf::Vector2f &pos) :
	Projectile(pos, "bullet")
{
	SetSpeed({xspeed, 0});
}

void Bullet::ApplyEffect (Player * target) {
	target->GetSprite().setPosition(target->GetInitPos());
	target->SetSpeed({0, 0});
	in_use = false;
}

void Bullet::ApplyResponse (const sf::Vector2f & vec) {
	in_use = false;
}

void Bullet::Update ( ) {
	m_sprite.move(m_speed.x, 0);
}

void Bullet::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

