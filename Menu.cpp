#include "Menu.h"
#include <sstream>
#include "Settings.h"
#include "phutils.h"
#include "Game.h"
Menu::Menu(float width, float height,std::string location) : 
	Escena(width, height),	frame_count(0),	current_option(0), 
	change_up(false), change_down(false),charge_select(true),m_location(location)
	/*charge select tiene que estar inicializado con true, 
	para evitar que al pasar de una escena de menu a otra se selecione en el primer frame_count
	de la nueva escena la primera opcion.
	*/
{


}

void Menu::LoadTexts ( ) 
{
	
	Settings s("texts.conf",m_location);
	m_font.loadFromFile(s["font"] + ".ttf");
	m_texts.resize( stoi(s["size"]) );
	m_Noptions=stoi(s["choosable"]);
	int r, g, b;
	std::stringstream ss;
	for (size_t i=0; i<m_texts.size(); ++i) 
	{ 
		m_texts[i].setFont(m_font);
		
		std::string key = "str" + std::to_string(i) + "-";
		std::string str = s[key+"set"];
		m_texts[i].setString(str);
		m_texts[i].setCharacterSize( stoi(s[key+"charsize"]) );
		
		ss << s[key+"color"];
		ss >> r >> g >> b;
		m_texts[i].setFillColor(sf::Color(r, g, b));
		sf::FloatRect text_rect = m_texts[i].getLocalBounds();
		m_texts[i].setOrigin( text_rect.left+text_rect.width/2, text_rect.top+text_rect.height/2 );
		m_texts[i].setPosition(win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]));
	}
}



void Menu::LoadKeys()
{
	Settings s("controls.conf","menu");
	m_input.BindKey("go_up",m_input<s["key-up"]);
	m_input.BindKey("go_down",m_input<s["key-down"]);
	m_input.BindKey("select",m_input<s["key-select"]);
}
void Menu::RandomizeMyColor(unsigned const& text_position)
{
	utils::HSV col((frame_count*3)%361, 100, 100);
	
	m_texts[text_position].setFillColor(col.MakeRGB());
	++frame_count;
}

void Menu::HighlightCurrentOption()
{
	for (size_t i=m_texts.size()-m_Noptions; i<m_texts.size(); ++i)
		m_texts[i].setFillColor({150, 150, 150, 150});
	m_texts[m_texts.size()-m_Noptions+current_option].setFillColor({255, 255, 255});
	//esto sirve para dar el efecto de selecionar la opcion actual 
	//(basicamente oscurece todos los textos selecionables menos el actual)
}

void Menu::Move_Option_Up()
{
	if (change_up != m_input["go_up"]) {
		change_up = !(change_up);
		if (change_up) {
			--current_option;
			if (current_option < 0)
				current_option = m_Noptions-1;
		}
	}
}
void Menu::Move_Option_Down()
{
	if (change_down != m_input["go_down"]) {
		change_down = !(change_down);
		if (change_down) {
			++current_option;
			if (current_option >= m_Noptions)
				current_option %= m_Noptions;
		}
	}
}
bool Menu::Is_Selected()
{
	bool b;
	if (charge_select != m_input["select"]) 
	{
		charge_select = !charge_select;
		b=true;
	}
	else b=false;
	return b;
}
