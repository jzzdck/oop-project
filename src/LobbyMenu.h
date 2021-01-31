#ifndef LOBBYMENU_H
#define LOBBYMENU_H
#include "Escena/Menu/Menu.h"
#include "MatchSettings.h"
#include <vector>
#include <string>
#include "Graphics/DrawingEnviroment.h"

class LobbyMenu : public Menu {
public:
	LobbyMenu(float width, float height);
	void ProcessEvent (sf::Event & e, Game & g) override;
	void Update (Game & g) override;
	void Render(DrawingEnviroment& drawEnv) override;
protected:
	void Select (Game & g) override;
private:
	std::string GetRandomMap();
	
	// Text replacing methods
	void ReplaceNumber(int index, int new_number, size_t starting_pos = 0);
	void ReplaceRoundType(int current, int next);
	void CenterText(int index);
	
	// attributes
	sf::Vector2f winsize;
	MatchSettings m_settings;
	std::vector<std::string> m_roundtypes;
	std::vector<std::string> m_descriptions;
};

#endif

