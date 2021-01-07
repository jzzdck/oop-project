#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity/Entity.h"

class Player;

class Projectile : public Entity {
public:
	Projectile(sf::Vector2f pos, std::string keyword);
	void Update() override;
	void Draw(sf::RenderWindow &win) override;
//	virtual void ApplyEffect(Player *target);
private:
	bool in_use;
};

#endif

