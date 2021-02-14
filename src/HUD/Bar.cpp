#include "Bar.h"
#include "../Utils/generalUtils.h"

Bar::Bar(std::string keyword) {
	FileManager settings("PlayerHUD.conf", keyword);
	m_relative_percentage = utils::getXY(settings["relative-percentage"]);
	
	sf::Vector2f size = utils::getXY(settings["size"]);
	m_width = size.x;
	m_background.setSize(size);
	m_bar.setSize(size);
	
	sf::Color color = utils::getColor(settings["background"]);
	m_background.setFillColor(color);
	
	color = utils::getColor(settings["foreground"]);
	m_bar.setFillColor(color);
}

void Bar::Render (const sf::Vector2f & hud_pos, DrawingEnviroment &drawEnv, float zoom_level, float dir) {
	sf::Vector2f aux = m_relative_percentage;
	if (dir == -1) aux.x = -m_relative_percentage.x;
	sf::Vector2f pos = utils::getFixedPos(drawEnv.getWin(), hud_pos, aux);
	
	if (with_background) {
		m_background.setPosition(pos);
		m_background.setScale(dir*zoom_level, zoom_level);
		drawEnv.AddToLayer(&m_background, 1);
	}
	
	m_bar.setPosition(pos);
	m_bar.setScale(dir*zoom_level, zoom_level);
	drawEnv.AddToLayer(&m_bar, 1);
}

void Bar::SetWidth (float new_width) {
	m_bar.setSize({m_width*new_width, m_bar.getSize().y});
}

void Bar::SetColor (const sf::Color & color) {
	m_bar.setFillColor(color);
}

