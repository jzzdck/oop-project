#include "HUD.h"
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"

HUD::HUD (const Player* target) : m_playercolor("player-color"), m_target(target)
{
	m_dir = target->GetIndex() ? 1.f : -1.f;
	FileManager s("PlayerHUD.conf", "HUD");
	
	m_relative_percentage = utils::getXY(s["relative_percentage"]);
	
	m_texture.loadFromFile("res/healthbar.png");
	m_hud.setTexture(m_texture);
	
	m_playercolor.SetColor(utils::loadPlayerColor(target->GetIndex()));
}

void HUD::Render (sf::RenderWindow & win, float zoom_level) {
	sf::Vector2f winsize = sf::Vector2f(win.getSize());
	
	m_pos = { 
		winsize.x * (m_relative_percentage.x + (m_dir == -1.f ? 0.9f : 0.0f)), 
		winsize.y * m_relative_percentage.y
	};
	
	m_healthbar.Render(m_pos, win, zoom_level, m_dir);
	m_playercolor.Render(m_pos, win, zoom_level, m_dir);
	m_ammobar.Render(m_pos, win, zoom_level, m_dir);
	DrawHUD(win, zoom_level);
}

void HUD::Update ( ) {
	m_healthbar.Update(m_target);
	m_ammobar.Update(m_target);
}

void HUD::DrawHUD (sf::RenderWindow & win, float zoom_level) {
	m_hud.setTexture(m_texture);
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(m_pos));
	m_hud.setPosition(pos);
	m_hud.setScale(m_dir*3*zoom_level, 3*zoom_level);
	win.draw(m_hud);
}
