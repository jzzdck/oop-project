#include "Shovel.h"

Shovel::Shovel(sf::Vector2f pos) : Weapon(pos, "shovel", 90, true, 0) {
	m_sprite.scale(2,2);
}

void Shovel::Draw(sf::RenderWindow & win) {
	win.draw(m_sprite);
}
