#include "MeleeHit.h"

MeleeHit::MeleeHit(const sf::Rect<float> &rect, float facing) : 
	Projectile(rect, "melee", rand()%(250-100)+100, facing, 0.15f) 
{
	
}

void MeleeHit::Update ( ) {
	if (lifetime.getElapsedTime().asSeconds() > 0.05f)
		in_use = false;
}

sf::Vector2f MeleeHit::GetPushbackForce ( ) {
	return {m_dir*10, 0};
}

