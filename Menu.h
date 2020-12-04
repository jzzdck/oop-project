#ifndef MENU_H
#define MENU_H
#include <vector>
#include <fstream>
#include <cstdlib>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Config.hpp>
#include "Scene.h"
#include "Match.h"
#include "Controls.h"
#include <string>

class Game;

class Menu : public Escena {
public:
	void Update(Game &g);
	void Draw(sf::RenderWindow &win);
	
	Menu(float width, float height,std::string location="principal");
private:
	void LoadTexts();
	void LoadKeys();
	std::string LoadHeadline();
	
	sf::Font m_font;
	std::vector<sf::Text> m_texts;
	std::string m_location;
	Controls m_input;
	int current_option;
	unsigned frame_count ,m_Noptions;
	bool change_up, change_down,charge_select;
};

#endif

