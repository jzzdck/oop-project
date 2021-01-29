#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"
#include "../../proyectile/Projectile.h"

class Revolver : public Weapon {
public:
	bool IsAttacking() override;
	/// @brief Construct a Revolver with a fixed damage.
	Revolver(sf::Vector2f pos, float facing);
private:
	bool is_shooting;
};

#endif

