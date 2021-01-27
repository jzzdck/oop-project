#ifndef BULLET_H
#define BULLET_H
#include "Projectile.h"

class Bullet : public Projectile {
public:
	Bullet(const sf::Vector2f &speed, const sf::Vector2f &pos);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void ApplyGravity(float gravity) override {};
	void Update ( ) override;
	void Render() override; 
private:
	bool first = true;
	sf::Clock impact_life;
	bool impacted = false;
};

#endif

