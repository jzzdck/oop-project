#include "MeleeHit.h"

MeleeHit::MeleeHit(const sf::Vector2f &pos) : 
	Projectile(pos, "melee", 250.f) 
{
	
}

void MeleeHit::Update ( ) {
	if (lifetime.getElapsedTime().asSeconds() > 0.05f)
		in_use = false;
}

