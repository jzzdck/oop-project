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
#include "../EntitiesFacade/PlayerInfo.h"
#include "../RoundSign.h"
#include "MatchHUD.h"

class MatchHUD : public sf::Drawable {
public:
	MatchHUD(const sf::Vector2f &winsize, std::string mapname, MatchSettings settings);
	void Render(DrawingEnviroment &drawEnv, float zoom_level);
	void Update(const std::vector<PlayerInfo> &info, int time);
	void Init(const std::vector<PlayerInfo> &info);
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	std::vector<HUD> m_playerHUDs;
	RoundSign m_roundsign;
};

#endif

