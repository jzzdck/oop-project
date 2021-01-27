#include "MatchHUD.h"
#include "../Utils/generalUtils.h"
#include "../Utils/FileManager.h"
#include <iostream>

MatchHUD::MatchHUD(const sf::Vector2f &winsize, std::string mapname) {
	m_font.loadFromFile("res/Chava-Regular.ttf");

	// cast the font (sized 40) to a texture and set its smoothness to false 
	const_cast<sf::Texture&>(m_font.getTexture(40)).setSmooth(false);
	m_roundpoint.setFont(m_font);
	m_roundpoint.setCharacterSize(25);
	m_roundpoint.setOutlineThickness(1);
	m_roundpoint.setOutlineColor(sf::Color::Black);

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

void MatchHUD::Render (sf::RenderWindow & win, float zoom_level, 
					 const std::vector<int> & roundpoints) 
{
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Render(win, zoom_level);
	
	win.draw(m_roundcounter);	

	sf::Vector2f relative_to = m_roundcounter.getPosition();
	for (size_t i=0; i<roundpoints.size(); ++i) { 
		m_roundpoint.setString(std::to_string(roundpoints[i]));
		m_roundpoint.setFillColor(utils::loadPlayerColor(i));
		m_roundpoint.setPosition({relative_to.x + 26.8f + float(i)*42, relative_to.y + 19});
		win.draw(m_roundpoint);
	}
}

void MatchHUD::Update () {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Update();	
}

