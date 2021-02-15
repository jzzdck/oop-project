#include "MatchHUD.h"
#include "../Utils/generalUtils.h"
#include "../Utils/FileManager.h"
#include <iostream>

MatchHUD::MatchHUD(const sf::Vector2f &winsize, std::string mapname, MatchSettings settings) :
	m_roundsign(winsize, settings)
{
	
}

void MatchHUD::Render (DrawingEnviroment &drawEnv, float zoom_level) 
{
	for (size_t i=0; i<m_playerHUDs.size(); ++i) { 
		m_playerHUDs[i].Render(drawEnv, zoom_level);
		drawEnv.AddToLayer(&m_playerHUDs.at(i), 1);
	}
	
	m_roundsign.Render(drawEnv, zoom_level);
	drawEnv.AddToLayer(&m_roundsign, 3);
}

void MatchHUD::Update (const std::vector<PlayerInfo> &info, int time) {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Update(info[i]);	

	m_roundsign.Update(info, time);
}

void MatchHUD::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	for (auto &huds : m_playerHUDs)
		target.draw(huds);
}

void MatchHUD::Init (const std::vector<PlayerInfo> & info) {
	for (size_t i=0; i<info.size(); ++i) {
		m_playerHUDs.push_back(HUD(i));
		m_playerHUDs.at(i).Update(info.at(i));
	}
}
