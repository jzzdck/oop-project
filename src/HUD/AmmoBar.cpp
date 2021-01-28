#include "AmmoBar.h"

AmmoBar::AmmoBar() : Bar("ammobar") {
	with_background = true;
}

void AmmoBar::Update (const HUDinfo &info) {
	Ammo ammo = info.ammo_data;
	float percentage = 1.f;
	
	if (ammo.max != 0)
		percentage = float(ammo.current)/float(ammo.max);
	
	if (percentage < 0)
		percentage = 0.f;
	
	SetWidth(percentage);
}

