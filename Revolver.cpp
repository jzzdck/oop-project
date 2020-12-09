#include "Revolver.h"
#include <iostream>

Revolver::Revolver(bool facing, float wdt) : 
	Weapon("revolver", 30, facing, wdt)
{ }

void Revolver::Attack ( ) {
	std::cout << "PEW" << std::endl;
}

void Revolver::Update() {
	m_sprite.setPosition(m_pos);
}

void Revolver::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[m_current]);
	win.draw(m_sprite);
}

