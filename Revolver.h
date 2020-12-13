#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"

/// @brief A revolver, the token weapon for now.
class Revolver : public Weapon {
public:
	void Draw(sf::RenderWindow &win) override;
	
	/// @brief Shoot.
	void Attack() override;
	
	/// @brief Construct a Revolver with a fixed damage.
	Revolver(sf::Vector2f pos, bool facing, float wdt);
private:
};

#endif

