#include "Flag.h"
#include "phutils.h"

Flag::Flag(float initial_y, float initial_x, bool who) : Item("box") {
	m_sprite.setPosition(initial_y, initial_x);
	m_sprite.setTexture(m_textures[!who]);
	m_sprite.scale(2,2);
	m_sprite.setColor(utils::loadPlayerColor(who));
}

void Flag::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

