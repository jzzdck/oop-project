#include "Weapon.h"

Weapon::Weapon(sf::Vector2f pos, std::string keyword, 
			   int damage, bool facing, float width) :
	Item(pos, keyword), 
	m_damage(damage), 
	m_current(facing), 
	m_width(width), attack_state(false)
{
	
}

void Weapon::SetText() {
	m_sprite.setTexture(m_textures[m_current]);
}

sf::Vector2f Weapon::OffSet(const sf::Vector2f &to_offset) {
	float x = to_offset.x;
	float y = to_offset.y;

	float offset = m_current ? -35.f : m_width+20.f;
	return sf::Vector2f(x+offset, y+35.f);
}

void Weapon::SetPos(const sf::Vector2f & relative_to, bool facing) {
	m_current = facing;
	m_pos = OffSet(relative_to);
	m_sprite.setPosition(m_pos);
}

