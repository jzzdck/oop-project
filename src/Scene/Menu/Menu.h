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
#include <string>
#include "../Scene.h"
#include "../../Utils/Controls.h"
#include "Slider.h"


class Menu : public Scene {
public:
	Menu(float width, float height,std::string location="principal");
	virtual ~Menu() = default;
private:
protected:
	///Load elements on contructor
	void LoadTexts();
	void LoadKeys();
	void LoadFigures();
	void LoadSliders();
	
	///Movement and actions in menu
	virtual void Select(Game& g)=0;
	void StandardMenuInput(Game &g, const sf::Keyboard::Key &keycode);
	void Move_Option(int dir);
	
	///TextOperations
	void RandomizeMyColor(unsigned const& text_position, int velocity);
	void HighlightCurrentOption();
	
	///Variables
	unsigned frame_count;
	
	int current_option;
	std::vector<Slider> m_sliders;
	std::vector<sf::RectangleShape> m_rectangles;
	std::vector<sf::Text> m_texts;
	sf::Vector2i m_Noptions;//los numeros son [x,y] inlcuyendo (y) 
	Controls m_input;
	sf::Font m_font;
	std::vector<sf::Color> m_text_color;
	std::string m_location;
};

#endif

