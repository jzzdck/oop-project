#ifndef BULLET_H
#define BULLET_H
#include "Projectile.h"

class Bullet : public Projectile {
public:
	Bullet(const sf::Vector2f &speed, const sf::Rect<float> &rect, float facing);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void Update ( ) override;
	void Render() override; 
	sf::Vector2f GetPushbackForce() override;
private:
	bool first = true;
	sf::Clock impact_life;
	bool impacted = false;
};

#endif

