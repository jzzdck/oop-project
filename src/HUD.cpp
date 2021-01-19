#include "HUD.h"
#include "Utils/generalUtils.h"

HUD::HUD (float dir, const sf::Vector2f &pos) : 
	m_dir(dir), m_pos(pos) 
{
	m_healthbar.resize(3); 
	for(size_t i=0;i<m_healthbar.size();i++) { 
		m_healthbar[i].setSize({210.f, 21.f});
		m_healthbar[i].setFillColor({169, 59, 59});
	}
	
	m_healthbar[2].setFillColor({75, 54, 56});
	
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
	
	pos = win.mapPixelToCoords(sf::Vector2i(m_pos.x + m_dir*7*3, m_pos.y + 3*20));
	m_healthbar[0].setPosition(pos);
	m_healthbar[0].setScale(m_dir*zoom_level, zoom_level);
	
	pos = win.mapPixelToCoords(sf::Vector2i(m_pos.x + m_dir*7*3, m_pos.y + 3*20));
	m_healthbar[2].setPosition(pos);
	m_healthbar[2].setScale(m_dir*zoom_level, zoom_level);
	
	win.draw(m_healthbar[2]);
	win.draw(m_healthbar[0]);
	win.draw(m_playercolor);
	win.draw(m_hud);
}

void HUD::Update ( ) {
	float health = m_target->GetHealth();
	if (health <= 0.f) health = 0.f;
	m_healthbar[0].setSize({health/1000.f * 210.f, 21.f});
}

void HUD::SetPlayer (const Player * target) {
	m_target = target;
}
