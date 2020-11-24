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
	sf::Text m_text1, m_text2;
	int frame_count;
};

#endif

