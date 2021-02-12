#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "../Player.h"
#include "../Entity.h"
#include "../../Utils/generalUtils.h"

class Projectile : public Entity {
public:
	Projectile(const sf::Rect<float> &rect, std::string keyword, float m_damage, float facing, float crit_chance);
	
	virtual void Render(DrawingEnviroment &drawEnv) { 
		utils::flipTexture(m_dir, m_scale, m_sprite);
	}
	
	virtual void Render() { 
		utils::flipTexture(m_dir, m_scale, m_sprite);
	}
	
	virtual void ApplyEffect(Player *target);
protected:
	float m_damage, crit_chance;
};

#endif

