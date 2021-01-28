#ifndef HANDCANNON_H
#define HANDCANNON_H
#include "Weapon.h"

class Handcannon : public Weapon {
public:
	void Render(DrawingEnviroment &drawEnv) override;
	Handcannon(sf::Vector2f pos, float facing);
	void Update() override;
	bool IsAttacking ( ) override;
	void SetPos(const sf::Rect<float> &relative_to, float facing) override;
	Projectile * GetProjectile ( ) override;
private:
	float m_angle = 0;
	float m_nextangle = 0;
	bool is_shooting = false;
};

#endif

