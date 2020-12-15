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
	Menu(float width, float height,std::string location="principal");
protected:
	///Load elements on contructor
	void LoadTexts();
	void LoadKeys();
	void LoadSliders();
	
	///Movement and actions in menu
	void Move_Option_Down();
	void Move_Option_Up();
	bool Move_Option_Left();
	bool Move_Option_Right();
	bool Is_Selected();
	void Move_MySlider(unsigned const slider_index,bool const direction);
	
	///TextOperations
	void RandomizeMyColor(unsigned const& text_position);
	void HighlightCurrentOption();
	void CopyColorFromPlayer(unsigned const& text_position);
	
	///Variables
	bool change_up, change_down,change_right,change_left,charge_select;
	unsigned frame_count, m_Noptions;
	int current_option;
	std::vector<sf::RectangleShape> m_sliders;
	std::vector<sf::Text> m_texts;
	sf::Vector2f m_slide_speed;
	sf::Color m_c;
	Controls m_input;
	sf::Font m_font;
	std::string m_location;
	
};

#endif

