#include "Bullet.h"
#include "Utils/phutils.h"

Bullet::Bullet(float xspeed, const sf::Vector2f &pos) :
	Projectile(pos, "bullet")
{
	SetSpeed({xspeed, 0});
	if (xspeed > 0) { 
		m_sprite.setTexture(m_textures[1]);
		m_sprite.move(16, 0);
	}
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

