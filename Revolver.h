#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"

class Revolver : public Weapon {
public:
	void Update() override;
	void Draw(sf::RenderWindow &win) override;
	void Attack() override;
	
	Revolver(bool facing, float wdt);
private:
};

#endif

