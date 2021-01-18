#include "HUD.h"
#include "Utils/generalUtils.h"

HUD::HUD (float dir, const sf::Vector2f &pos) : 
	m_dir(dir), m_pos(pos) 
{
	m_texture.loadFromFile("res/healthbar.png");
	m_hud.setTexture(m_texture);
	m_hud.setPosition(m_pos);
	
	m_playercolor.setSize({30.f,30.f});
	m_playercolor.setFillColor(utils::loadPlayerColor(m_dir == 1 ? 0 : 1));
}

void HUD::Draw (sf::RenderWindow & win, float zoom_level) {
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_pos));
	m_hud.setPosition(pos);
	
	pos = win.mapPixelToCoords(sf::Vector2i(m_pos.x + m_dir*45, m_pos.y + 15));
	m_playercolor.setPosition(pos);
	
	m_playercolor.setScale(m_dir*zoom_level, 1.f*zoom_level);
	m_hud.setScale(m_dir*3*zoom_level, 3*zoom_level);
	
	win.draw(m_playercolor);
	win.draw(m_hud);
}

void HUD::Update ( ) {
}

void HUD::SetPlayer (const Player * target) {
	
}
