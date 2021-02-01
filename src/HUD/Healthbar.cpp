#include "Healthbar.h"

HealthBar::HealthBar() : Bar("healthbar") {
	with_background = true;
}

void HealthBar::Update (const PlayerInfo &info) {
	HealthData h = info.health_data;
	float current = h.current_health;
	if (h.current_health <= 0.f) 
		current = 0.f;
	
	this->SetWidth(current/h.max_health);
}
