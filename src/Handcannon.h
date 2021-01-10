#ifndef HANDCANNON_H
#define HANDCANNON_H
#include "Entity/Item/Weapon/Weapon.h"

class Handcannon : public Weapon {
public:
	void Draw(sf::RenderWindow &win) override;
	Handcannon(sf::Vector2f pos, bool facing);
	bool IsAttacking ( ) override;
	Projectile * GetProjectile ( ) override;
private:
	float m_bombspeed = 0;
	float m_nextspeed = 0;
	bool is_shooting = false;
};

#endif

