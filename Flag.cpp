#include "Flag.h"
#include "phutils.h"

Flag::Flag(sf::Vector2f pos, bool who) : Item(pos, "box") {
	m_sprite.setTexture(m_textures[!who]);
	m_sprite.scale(2,2);
	m_sprite.setColor(utils::loadPlayerColor(who));
}

void Flag::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

