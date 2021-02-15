#ifndef TESLAGUN_H
#define TESLAGUN_H
#include "Weapon.h"

class TeslaGun : public Weapon {
public:
	TeslaGun(const sf::Vector2f &pos, float facing);
	bool IsAttacking ( ) override;
private:
	bool shot = false;
};

#endif

