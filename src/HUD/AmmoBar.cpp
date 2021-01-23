#include "AmmoBar.h"

AmmoBar::AmmoBar() : Bar("ammobar") {
	with_background = true;
}

void AmmoBar::Update (const Player * target) {
	sf::Vector2i ammo = target->GetAmmo();
	float percentage = 1.f;
	
	if (ammo.y != 0)
		percentage = float(ammo.x)/float(ammo.y);
	
	if (percentage < 0)
		percentage = 0.f;
	
	SetWidth(percentage);
}

