#ifndef BULLET_H
#define BULLET_H
#include "Projectile.h"
#include "../../Graphics/DrawingEnviroment.h"

class Bullet : public Projectile {
public:
	Bullet(const sf::Vector2f &speed, const sf::Rect<float> &rect, float facing);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void Update ( ) override;
	void ApplyEffect(Player *target) override;
	void Render(DrawingEnviroment &drawEnv) override; 
	sf::Vector2f GetPushbackForce() override;
private:
	sf::RectangleShape ray;
	sf::Vector2f pos;
	bool first = true;
	sf::Clock impact_life;
	bool impacted = false;
};

#endif

