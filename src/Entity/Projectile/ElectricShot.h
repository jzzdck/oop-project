#ifndef ELECTRICSHOT_H
#define ELECTRICSHOT_H
#include "Projectile.h"

class ElectricShot : public Projectile {
public:
	ElectricShot(const sf::Rect<float> &rect, float facing);
	void ApplyEffect (Player * target) override;
	void Render () override;
	void Update ( ) override;
private:
	sf::Clock m_lifetime;
};

#endif

