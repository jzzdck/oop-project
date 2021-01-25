#ifndef MATCHHUD_H
#define MATCHHUD_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "HUD.h"
#include "../Entity/Player.h"
#include "MatchHUD.h"
using namespace std;

class MatchHUD {
public:
	MatchHUD(const sf::Vector2f &winsize, std::string mapname);
	void SetPlayers(std::vector<Player*> players);
	void Draw(sf::RenderWindow &win, float zoom_level, const std::vector<int> &roundpoints);
	void Update();
private:
	std::vector<HUD> m_playerHUDs;

	sf::Text m_roundpoint;
	sf::Font m_font;
	
	sf::Sprite m_roundcounter;
	sf::Texture m_texture;
};

#endif

