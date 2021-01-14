#include "Flag.h"
#include "../../Utils/generalUtils.h"

Flag::Flag(sf::Vector2f pos, bool who) : Item(pos, "box") {
	m_sprite.setTexture(m_textures[!who]);
	m_sprite.setColor(utils::loadPlayerColor(who));
}

void Flag::Draw (sf::RenderWindow & win) {
	win.draw(m_sprite);
}

