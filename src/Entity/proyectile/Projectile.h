#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "../Player.h"
#include "../Entity.h"
#include "../../Utils/generalUtils.h"

class Player;

class Projectile : public Entity {
public:
	Projectile(sf::Vector2f pos, std::string keyword, float m_damage);
	bool IsUsed() const { return in_use; }
	virtual void Draw(sf::RenderWindow &win) { 
		utils::flipTexture(m_dir, m_scale, m_sprite);
		win.draw(m_sprite); 
	}
	
	virtual void ApplyEffect(Player *target);
protected:
	bool in_use = true;
	float m_damage;
};

#endif

