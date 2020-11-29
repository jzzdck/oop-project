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

class Game;

class Menu : public Escena {
public:
	Menu(float width, float height);
	void Update(Game &g);
	void Draw(sf::RenderWindow &win);
private:
	sf::Font m_font;
	std::vector<sf::Text> m_texts;
	
	int frame_count, current_option;
	bool change_up, change_down;
};

#endif

