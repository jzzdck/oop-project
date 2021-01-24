#include "MatchHUD.h"
#include "../Utils/generalUtils.h"


MatchHUD::MatchHUD() {
	m_font.loadFromFile("res/Chava-Regular.ttf");
	m_roundpoint.setFont(m_font);
	m_roundpoint.setCharacterSize(30);
	m_roundpoint.setOutlineColor({0,0,0});
	m_roundpoint.setOutlineThickness(2);	
}

void MatchHUD::SetPlayers(std::vector<Player*> players) {
	for (size_t i=0; i<players.size(); ++i)
		m_playerHUDs.push_back( HUD(players[i]) );
}

void MatchHUD::Draw (sf::RenderWindow & win, float zoom_level, const std::vector<int> & roundpoints) {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Draw(win, zoom_level);
	
	for (size_t i=0; i<roundpoints.size(); ++i) { 
		m_roundpoint.setString("x" + std::to_string(roundpoints[i]));
		m_roundpoint.setFillColor(utils::loadPlayerColor(i));
		m_roundpoint.setPosition({float(i)*200, 200});
		win.draw(m_roundpoint);
	}
}

void MatchHUD::Update () {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Update();	
}

