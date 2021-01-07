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
	int x = to_offset.x;
	int y = to_offset.y;

	int offset = m_current ? -35 : m_width;
	return sf::Vector2f(x+offset, y+35);
}

void Weapon::SetPos(const sf::Vector2f & relative_to, bool facing) {
	m_current = facing;
	m_pos = OffSet(relative_to);
}
