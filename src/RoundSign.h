#ifndef ROUNDSIGN_H
#define ROUNDSIGN_H
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "EntitiesFacade/PlayerInfo.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Scene/Match/MatchSettings.h"

class RoundSign : public sf::Drawable {
public:
	RoundSign(const sf::Vector2f &winsize, MatchSettings settings);
	void Update(const std::vector<PlayerInfo> &info, int time);
	void Render(DrawingEnviroment &drawEnv, float zoom_level);
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	
	MatchSettings m_settings;
	std::vector<sf::Vector2f> m_relativepos;
	sf::Vector2f winsize;
	std::vector<sf::Text> m_roundpoint;
	sf::Text m_timer;
	sf::Font m_font;
	sf::Sprite m_roundcounter;
	sf::Texture m_texture;
};

#endif

