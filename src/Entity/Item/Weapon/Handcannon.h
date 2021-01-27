#ifndef HANDCANNON_H
#define HANDCANNON_H
#include "Weapon.h"

class Handcannon : public Weapon {
public:
	void Render() override;
	Handcannon(sf::Vector2f pos, float facing);
	bool IsAttacking ( ) override;
	Projectile * GetProjectile ( ) override;
private:
	float m_angle = 0;
	float m_nextangle = 0;
	bool is_shooting = false;
};

#endif

