#ifndef REVOLVER_H
#define REVOLVER_H
#include "Weapon.h"
#include "../../proyectile/Projectile.h"

class Revolver : public Weapon {
public:
	void Draw(sf::RenderWindow &win) override;
	bool IsAttacking() override;
	Projectile* GetProjectile() override;
	/// @brief Construct a Revolver with a fixed damage.
	Revolver(sf::Vector2f pos, bool facing);
private:
	bool is_shooting;
};

#endif

