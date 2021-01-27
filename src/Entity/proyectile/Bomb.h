#ifndef BOMB_H
#define BOMB_H
#include "Projectile.h"
#include "../../Graphics/Trail.h"

class Bomb : public Projectile {
public:
	Bomb(const sf::Vector2f &vel, const sf::Vector2f &pos);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void ApplyEffect (Player * target) override;
	void ApplyGravity(float gravity) override;
	void Update ( ) override;
	void Explode();
	void Render() override;
private:
	bool exploding = false;
	float max_life = 1.2f;
	sf::Clock timer, lifetime;
	
	Trail m_trail;
	/*Trail m_trail; construct with sprite, pass on pos vector, 
	make smaller towards radius, erase last one, give decreasing alpha values*/
};

#endif

