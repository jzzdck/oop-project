#include "Flag.h"
#include "../../Utils/generalUtils.h"

Flag::Flag(sf::Vector2f pos, bool who) : Item(pos, "suitcase") {
	m_sprite.setTexture(m_textures[0]);
	
	m_dep.setTexture(m_textures[1]);
	m_dep.setColor(utils::loadPlayerColor(who));
	m_dep.setOrigin(m_dep.getGlobalBounds().width, 0);
	m_dep.scale(2,2);
	m_dep.setPosition(pos);
}

void Flag::Draw (sf::RenderWindow & win) {
	m_dep.setPosition(m_sprite.getPosition());
	win.draw(m_sprite);
	win.draw(m_dep);
}

