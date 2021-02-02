#include "MeleeHit.h"

MeleeHit::MeleeHit(const sf::Rect<float> &rect, float facing) : 
	Projectile(rect, "melee", 250.f, facing) 
{
	
}

void MeleeHit::Update ( ) {
	if (lifetime.getElapsedTime().asSeconds() > 0.05f)
		in_use = false;
}
