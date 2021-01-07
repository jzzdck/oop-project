#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, std::string keyword) : 
	Entity(pos, keyword)
{ }

//void Projectile::ApplyEffect (Player * target) {
//	target->GetSprite().setPosition(target->GetInitPos());
//	target->SetSpeed({0, 0});
//}

void Projectile::Update ( ) {
	m_sprite.move(-15, 0);
}

void Projectile::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

