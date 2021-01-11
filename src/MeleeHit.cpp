#include "MeleeHit.h"

MeleeHit::MeleeHit(const sf::Vector2f &pos) : 
	Projectile(pos, "melee") 
{
	
}

void MeleeHit::ApplyResponse (const sf::Vector2f & vec) {
	return;
}

void MeleeHit::Update ( ) {
	if (lifetime.getElapsedTime().asSeconds() > 0.05f)
		in_use = false;
}

void MeleeHit::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

