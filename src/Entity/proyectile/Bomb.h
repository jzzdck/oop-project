#ifndef BOMB_H
#define BOMB_H
#include "Projectile.h"

class Bomb : public Projectile {
public:
	Bomb(const sf::Vector2f &vel, const sf::Vector2f &pos);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void ApplyEffect (Player * target) override;
	void Update ( ) override;
	void Explode();
private:
	bool exploding = false;
	float max_life = 1.2f;
	sf::Clock timer, lifetime;
};

#endif

