#ifndef MELEEHIT_H
#define MELEEHIT_H
#include "Projectile.h"

class MeleeHit : public Projectile {
public:
	MeleeHit(const sf::Rect<float> &rect, float facing);
	void ApplyResponse (const sf::Vector2f & vec) override {}
	void Update ( ) override;
private:
	sf::Clock lifetime;
};

#endif

