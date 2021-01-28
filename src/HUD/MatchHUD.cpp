#include "MatchHUD.h"
#include "../Utils/generalUtils.h"
#include "../Utils/FileManager.h"
#include <iostream>

MatchHUD::MatchHUD(const sf::Vector2f &winsize, std::string mapname) {
	m_font.loadFromFile("res/Chava-Regular.ttf");

	m_roundpoint.resize(2);
	for(size_t i=0;i<m_roundpoint.size();i++) {
		m_roundpoint.at(i).setFont(m_font);
		m_roundpoint.at(i).setCharacterSize(25);
		m_roundpoint.at(i).setOutlineThickness(1);
		m_roundpoint.at(i).setOutlineColor(sf::Color::Black);
	}

	FileManager s("MatchHUD.conf", "round-sign");
	m_texture.loadFromFile(s["texture"] +  ".png");
	m_roundcounter.setTexture(m_texture);
	
	sf::Vector2f percentages = utils::getXY(s[mapname + "-pos"]);
	m_roundcounter.setPosition( 
		{ winsize.x * percentages.x, 
		  winsize.y * percentages.y } 
	);
	
	m_roundcounter.scale(2.f, 2.f);
}

void MatchHUD::SetPlayers(std::vector<Player*> players) {
	for (size_t i=0; i<players.size(); ++i)
		m_playerHUDs.push_back( HUD(players[i]) );
}


void MatchHUD::Render (DrawingEnviroment &drawEnv, float zoom_level, 
					 const std::vector<int> & roundpoints) 
{
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Render(drawEnv, zoom_level);
	
	sf::Vector2f relative_to = m_roundcounter.getPosition();
	for (size_t i=0; i<roundpoints.size(); ++i) { 
		m_roundpoint.at(i).setString(std::to_string(roundpoints[i]));
		m_roundpoint.at(i).setFillColor(utils::loadPlayerColor(i));
		m_roundpoint.at(i).setPosition({relative_to.x + 26.8f + float(i)*42, relative_to.y + 19});
	}
	
	drawEnv.AddToLayer(&m_roundcounter, 3);
	for(size_t i=0;i<m_roundpoint.size();i++)
		drawEnv.AddToLayer(&m_roundpoint.at(i), 3);
	
	for(size_t i=0;i<m_playerHUDs.size();i++)
		drawEnv.AddToLayer(&m_playerHUDs.at(i), 0);
}

void MatchHUD::Update () {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Update();	
}

void MatchHUD::draw (sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_roundcounter);
	
	for(size_t i=0;i<m_roundpoint.size();i++) {
		target.draw(m_roundpoint.at(i));
		target.draw(m_playerHUDs.at(i));
}

void MatchHUD::SetRoundState (const std::vector<int> & new_roundpoints) {
	roundpoints = new_roundpoints;
}

