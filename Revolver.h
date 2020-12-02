#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"

class Revolver : public Weapon {
public:
	Revolver(bool facing, float wdt);
	void Draw(sf::RenderWindow &win) override;
	void Update() override;
	void Attack() override;
private:
};

#endif

