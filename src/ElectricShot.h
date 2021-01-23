#ifndef ELECTRICSHOT_H
#define ELECTRICSHOT_H
#include "Entity/proyectile/Projectile.h"

class ElectricShot : public Projectile {
public:
	ElectricShot(sf::Rect<float> rect, const sf::Vector2f &pos, float facing);
	void ApplyEffect (Player * target) override;
	void Draw (sf::RenderWindow & win) override;
	void Update ( ) override;
private:
	sf::Clock m_lifetime;
};

#endif

