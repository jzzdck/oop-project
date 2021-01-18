#include "HUD.h"

HUD::HUD() {
	m_texture.loadFromFile("res/healthbar.png")
	m_hud.setTexture(m_texture)
}

void HUD::Draw (sf::RenderWindow & win) {
	win.draw(m_hud);
}

void HUD::SetPlayers (std::vector<Player*> m_players) {
	m_players = players;
}

void HUD::Update ( ) {
	m_hud.setPosition(center);
}

void HUD::SetCenter (sf::Vector2f & center) {
	m_center = center;
}

