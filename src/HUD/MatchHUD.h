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
#include "../Graphics/DrawingEnviroment.h"
#include "../PlayerInfo.h"

class MatchHUD : public sf::Drawable {
public:
	MatchHUD(const sf::Vector2f &winsize, std::string mapname);
	void Render(DrawingEnviroment &drawEnv, float zoom_level);
	void Update(const std::vector<PlayerInfo> &info);
	void Init(const std::vector<PlayerInfo> &info);
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	std::vector<HUD> m_playerHUDs;

	std::vector<sf::Text> m_roundpoint;
	sf::Font m_font;
	
	sf::Sprite m_roundcounter;
	sf::Texture m_texture;
};

#endif

