#include "MatchHUD.h"

MatchHUD::MatchHUD() {
}

void MatchHUD::SetPlayers(std::vector<Player*> players) {
	for (size_t i=0; i<players.size(); ++i)
		m_playerHUDs.push_back( HUD(players[i]) );
}

void MatchHUD::Draw (sf::RenderWindow & win, float zoom_level) {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Draw(win, zoom_level);
}

void MatchHUD::Update ( ) {
	for (size_t i=0; i<m_playerHUDs.size(); ++i) 
		m_playerHUDs[i].Update();
}

