#ifndef BULLET_H
#define BULLET_H
#include "Projectile.h"

class Bullet : public Projectile {
public:
	Bullet(float xspeed, const sf::Vector2f &pos);
	void ApplyEffect (Player * target) override;
	void ApplyResponse (const sf::Vector2f & vec) override;
	void Update ( ) override;
	void Draw (sf::RenderWindow & win) override;
private:
};

#endif

