#include "RoundSign.h"
#include "Utils/generalUtils.h"
#include <iostream>

RoundSign::RoundSign (const sf::Vector2f &winsize, MatchSettings settings) :
	winsize(winsize), m_settings(settings)
{	
	m_font.loadFromFile("../res/Chava-Regular.ttf");
	m_roundpoint.resize(2);
	m_relativepos.resize(3);
	for(size_t i=0;i<m_roundpoint.size();i++) {
		m_roundpoint.at(i).setFont(m_font);
		m_roundpoint.at(i).setCharacterSize(25);
		m_roundpoint.at(i).setOutlineThickness(3);
		m_roundpoint.at(i).setOutlineColor({20, 20, 20});
	}
	
	FileManager s("MatchHUD.conf", "round-sign");
	m_texture.loadFromFile(s["texture"] +  ".png");
	for (size_t i=0; i<m_relativepos.size(); ++i)
		m_relativepos.at(i) = utils::getXY(s["relative" + std::to_string(i)]);
	
	m_roundcounter.setTexture(m_texture);
	if (settings.round_type == 1)
		m_roundcounter.setTextureRect({0,0,52,22});
	
	m_timer.setFont(m_font);
	m_timer.setFillColor(sf::Color::White);
	m_timer.setOutlineThickness(3);
	m_timer.setCharacterSize(15);
	m_timer.setOutlineColor({20, 20, 20});
	
	for (size_t i=0; i<m_roundpoint.size(); ++i)
		m_roundpoint.at(i).setFillColor(utils::loadPlayerColor(i));
}

void RoundSign::Update ( const std::vector<PlayerInfo> &info, int time ) {	
	for (size_t i=0; i<info.size(); ++i) {
		int aux = info.at(i).round_points;
		if (m_settings.round_type != 2)
			aux = m_settings.max_points - aux;
		m_roundpoint.at(i).setString(std::to_string(aux));
	}
	
	m_timer.setString(std::to_string(m_settings.max_seconds - time));
}

void RoundSign::Render (DrawingEnviroment & drawEnv, float zoom_level) {
	sf::Vector2f abpos(0.42382813f, 0.03f);
	sf::Vector2f aux = utils::getFixedPos(drawEnv.getWin(), abpos, {0,0});
	m_roundcounter.setScale(3.f*zoom_level, 3.f*zoom_level);
	m_roundcounter.setPosition(aux);
	drawEnv.AddToLayer(&m_roundcounter, 2);	
	
	for (size_t i=0; i<m_roundpoint.size(); ++i) {
		aux = utils::getFixedPos(drawEnv.getWin(), abpos, m_relativepos.at(i));
		m_roundpoint.at(i).setScale(zoom_level, zoom_level);
		m_roundpoint.at(i).setOrigin(utils::getCenter(m_roundpoint.at(i).getLocalBounds()));
		m_roundpoint.at(i).setPosition(aux);
		drawEnv.AddToLayer(&m_roundpoint.at(i), 1);
	}
	
	if (m_settings.round_type != 1) {
		aux = utils::getFixedPos(drawEnv.getWin(), abpos, m_relativepos.at(2));
		m_timer.setScale(zoom_level, zoom_level);
		m_timer.setOrigin(utils::getCenter(m_timer.getLocalBounds()));
		m_timer.setPosition(aux);
		drawEnv.AddToLayer(&m_timer, 1);
	}
}

void RoundSign::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_timer);
	for (auto &text : m_roundpoint)
		target.draw(text);
	target.draw(m_roundcounter);
}

