#ifndef MATCHHUD_H
#define MATCHHUD_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "HUD.h"
#include "../Entity/Player.h"
#include "MatchHUD.h"
#include "../Graphics/DrawingEnviroment.h"
using namespace std;

class MatchHUD : public sf::Drawable {
public:
	MatchHUD(const sf::Vector2f &winsize, std::string mapname);
	void SetPlayers(std::vector<Player*> players);
	void Render(DrawingEnviroment &drawEnv, float zoom_level, const std::vector<int> &roundpoints);
	void SetRoundState(const std::vector<int> &new_roundpoints);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void Update();
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	std::vector<HUD> m_playerHUDs;
	std::vector<int> roundpoints;

	std::vector<sf::Text> m_roundpoint;
	sf::Font m_font;
	
	sf::Sprite m_roundcounter;
	sf::Texture m_texture;
};

#endif

