#include "Revolver.h"
#include <iostream>

Revolver::Revolver(sf::Vector2f pos, bool facing, float wdt) : 
	Weapon(pos, "revolver", 30, facing, wdt)
{ }

void Revolver::Action ( ) {
	std::cout << "PEW" << std::endl;
}

void Revolver::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[m_current]);
	win.draw(m_sprite);
}

