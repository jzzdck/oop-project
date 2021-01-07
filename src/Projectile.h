#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Entity/Entity.h"
#include "Entity/Player.h"

class Player;

class Projectile : public Entity {
public:
	Projectile(sf::Vector2f pos, std::string keyword);
	bool IsUsed() const { return in_use; }
	virtual void ApplyEffect(Player *target) = 0;
protected:
	bool in_use = true;
};

#endif

