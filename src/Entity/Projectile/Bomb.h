#ifndef BOMB_H
#define BOMB_H
#include "Projectile.h"
#include "../../Graphics/Trail.h"
#include "../../Graphics/DrawingEnviroment.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Graphics/Animation.h"
#include "../../Utils/HSV.h"

class Bomb : public Projectile {
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	Bomb(const sf::Vector2f &vel, const sf::Rect<float> &rect, float facing);
	void ApplyResponse (const sf::Vector2f & vec) override;
	void ApplyEffect (Player * target) override;
	void Update ( ) override;
	void Explode();
	void Render() override {};
	void Render(DrawingEnviroment &drawEnv) override;
	sf::Vector2f GetPushbackForce() override;
private:
	bool exploding = false;
	Animation explosion;
	float max_life = 1.2f;
	sf::Clock timer, lifetime;
	
	Trail m_trail;
	utils::HSV trail_color;
};

#endif

