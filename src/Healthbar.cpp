#include "Healthbar.h"

HealthBar::HealthBar() : Bar("healthbar") {
	with_background = true;
}

void HealthBar::Update (const Player * target) {
	float health = target->GetHealth();
	if (health <= 0.f) 
		health = 0.f;
	
	this->SetWidth(health/1000.f);
}

