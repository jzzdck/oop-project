#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"

/// @brief A revolver, the token weapon for now.
class Revolver : public Weapon {
public:
	void Update() override;
	void Draw(sf::RenderWindow &win) override;
	
	/// @brief Shoot.
	void Attack() override;
	
	/// @brief Connstruct a Revolver with a fixed damage.
	Revolver(bool facing, float wdt);
private:
};

#endif

