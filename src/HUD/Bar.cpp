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
	auto &win = *drawEnv.getWin();
	sf::Vector2f winsize = sf::Vector2f(win.getSize());
	
	sf::Vector2f relative_pos = {
		winsize.x * m_relative_percentage.x * dir, 
		winsize.y * m_relative_percentage.y
	};
	
	sf::Vector2f pos = win.mapPixelToCoords(sf::Vector2i(hud_pos + relative_pos));
	
	if (with_background) {
		m_background.setPosition(pos);
		m_background.setScale(dir*zoom_level, zoom_level);
		drawEnv.AddToLayer(&m_background, 0);
	}
	
	m_bar.setPosition(pos);
	m_bar.setScale(dir*zoom_level, zoom_level);
	
	drawEnv.AddToLayer(&m_bar, 0);
}

void Bar::SetWidth (float new_width) {
	m_bar.setSize({m_width*new_width, m_bar.getSize().y});
}

void Bar::Update (const Player * target) {
	return;
}

void Bar::SetColor (const sf::Color & color) {
	m_bar.setFillColor(color);
}

