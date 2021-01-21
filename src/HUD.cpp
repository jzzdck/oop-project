#include "HUD.h"
#include "Utils/generalUtils.h"
#include "Utils/FileManager.h"

HUD::HUD (const Player* target) : m_target(target)
{
	m_dir = target->GetIndex() ? 1.f : -1.f;
	FileManager s("PlayerHUD.conf", "HUD");
	
	m_auxpos.resize(std::stoi(s["aux-size"]));
	for (size_t i=0; i<m_auxpos.size(); ++i)
		m_auxpos[i] = utils::getXY(s["aux-" + std::to_string(i)]);
	
	m_healthbar.resize(3); 
	for(size_t i=0;i<m_healthbar.size();i++) { 
		m_healthbar[i].setSize({216.f, 24.f});
		m_healthbar[i].setFillColor(utils::getColor(s["color-"+std::to_string(i)]));
	}
	
	m_texture.loadFromFile("res/healthbar.png");
	m_hud.setTexture(m_texture);
	
	m_playercolor.setSize({48.f, 48.f});
	m_playercolor.setFillColor(utils::loadPlayerColor(target->GetIndex()));
}

void HUD::Draw (sf::RenderWindow & win, float zoom_level) {
	winsize = sf::Vector2f(win.getSize());
	
	m_pos = { 
		winsize.x * (m_auxpos[0].x + (m_dir == -1.f ? 0.9f : 0.0f)), 
		winsize.y * m_auxpos[0].y
	};
	
	DrawHealthbar(win, zoom_level);
	DrawPlayerColor(win, zoom_level);
	DrawHUD(win, zoom_level);
}

void HUD::Update ( ) {
	float health = m_target->GetHealth();
	if (health <= 0.f) 
		health = 0.f;
	m_healthbar[2].setSize({health/1000.f * 216.f, 24.f});
}

void HUD::SetPlayer (const Player * target) {
	m_target = target;
}

void HUD::DrawHUD (sf::RenderWindow & win, float zoom_level) {
	m_hud.setTexture(m_texture);
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_pos));
	m_hud.setPosition(pos);
	m_hud.setScale(m_dir*3*zoom_level, 3*zoom_level);
	win.draw(m_hud);
}

void HUD::DrawPlayerColor (sf::RenderWindow & win, float zoom_level) {
	sf::Vector2f aux = {
		winsize.x * m_auxpos[1].x * m_dir, 
		winsize.y * m_auxpos[1].y
	};
	
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_pos + aux));
	m_playercolor.setPosition(pos);
	m_playercolor.setScale(m_dir*zoom_level, zoom_level);
	win.draw(m_playercolor);
}

void HUD::DrawHealthbar (sf::RenderWindow & win, float zoom_level) {
	sf::Vector2f aux = {
		winsize.x * m_auxpos[2].x * m_dir, 
		winsize.y * m_auxpos[2].y
	};
	
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_pos + aux));
	for (size_t i=0; i<m_healthbar.size(); ++i) { 
		m_healthbar[i].setPosition(pos);
		m_healthbar[i].setScale(m_dir*zoom_level, zoom_level);
		if (i != 1) win.draw(m_healthbar[i]);
	}
}

