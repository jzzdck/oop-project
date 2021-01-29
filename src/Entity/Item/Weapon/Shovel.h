#ifndef SHOVEL_H
#define SHOVEL_H
#include "Weapon.h"
#include <iostream>

class Shovel : public Weapon {
public:
	Shovel(sf::Vector2f pos);
	bool IsAttacking() override;
private:
	bool is_attacking = false;
};

#endif

