#ifndef LOBBYMENU_H
#define LOBBYMENU_H
#include <vector>
#include <string>
#include "Menu.h"
#include "../Match/MatchSettings.h"
#include "../../Graphics/DrawingEnviroment.h"
#include "../../Game.h"

class LobbyMenu : public Menu {
public:
	LobbyMenu(float width, float height);
	void ProcessEvent (sf::Event & e, Game & g) override;
	void Update (Game & g) override;
	void Render(DrawingEnviroment& drawEnv) override;
protected:
	void Select (Game & g) override;
private:
	// attributes
	sf::Vector2f winsize;
	MatchSettings m_settings;
	std::vector<std::string> m_roundtypes;
	std::vector<std::string> m_descriptions;
};

#endif

