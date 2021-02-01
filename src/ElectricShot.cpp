#include "ElectricShot.h"

ElectricShot::ElectricShot(const sf::Rect<float> &rect, float facing) : 
	Projectile(rect, "electricshot", 100.f, facing) 
{
	
}

void ElectricShot::ApplyEffect (Player * target) {
//	target->UnassignObjects();
	Projectile::ApplyEffect(target);
}

void ElectricShot::Render () 
{
	
}

void ElectricShot::Update ( ) {
	if (m_lifetime.getElapsedTime().asSeconds() >= 0.5f)
		in_use = false;
}
