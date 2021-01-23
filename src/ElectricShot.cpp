#include "ElectricShot.h"

ElectricShot::ElectricShot(sf::Rect<float> rect, const sf::Vector2f &pos, float facing) : 
	Projectile(pos, "electricshot", 100.f) 
{
	if (facing == -1.f) {
		utils::flipTexture(facing, m_scale, m_sprite);
		m_sprite.move(-rect.width - m_sprite.getGlobalBounds().width, 0);
	} else 
		utils::flipTexture(facing, m_scale, m_sprite);
}

void ElectricShot::ApplyEffect (Player * target) {
	target->UnassignObjects();
	Projectile::ApplyEffect(target);
}

void ElectricShot::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

void ElectricShot::Update ( ) {
	if (m_lifetime.getElapsedTime().asSeconds() >= 0.5f)
		in_use = false;
}

