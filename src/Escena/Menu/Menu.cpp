#include "Menu.h"
#include <sstream>
#include "../../FileManager.h"
#include "../../Utils/phutils.h"
Menu::Menu(float width, float height,std::string location) : 
	Escena(width, height),	frame_count(0),	current_option(0), 
	m_location(location)
{
	LoadTexts();
	LoadKeys();
}

void Menu::LoadTexts ( ) 
{
	FileManager s("texts.conf",m_location);
	m_font.loadFromFile(s["font"] + ".ttf");
	m_texts.resize( stoi(s["size"]) );
	std::string choices=s["choosable"];
	int choice_min=stoi(choices.substr(0,choices.find(",")));
	int choice_max=stoi(choices.substr(choices.find(",")+1,choices.size()));
	m_Noptions={choice_min,choice_max};
	
	
	for (size_t i=0; i<m_texts.size(); ++i) 
	{ 
		m_texts[i].setFont(m_font);
		
		std::string key = "str" + std::to_string(i) + "-";
		std::string str = s[key+"set"];
		m_texts[i].setString(str);
		m_texts[i].setCharacterSize( stoi(s[key+"charsize"]) );
		
		m_texts[i].setFillColor(utils::getColor( s[key+"color"]) );
		m_texts[i].setOrigin(utils::getCenter(m_texts[i].getLocalBounds()));
		m_texts[i].setPosition(win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]));
	}
}

void Menu::LoadKeys()
{
	FileManager s("controls.conf","menu");
	m_input.BindKey("go_up",m_input<s["key-up"]);
	m_input.BindKey("go_down",m_input<s["key-down"]);
	m_input.BindKey("select",m_input<s["key-select"]);
	m_input.BindKey("go_right",m_input<s["key-right"]);
	m_input.BindKey("go_left",m_input<s["key-left"]);
}
void Menu::LoadFigures()
{
	FileManager s("figures.conf", "figures of "+m_location);
	m_rectangles.resize(stoi(s["size"]));
	sf::Color c = utils::getColor(s["color"]);
	for (size_t i=0; i<m_rectangles.size(); ++i) {
		std::string key = "rect" + std::to_string(i) + "-"; //recti-w, recti-h, etc
		sf::Vector2f dim = { win_width * stof(s[key+"w"]), win_height * stof(s[key+"h"]) };
		sf::Vector2f pos = { win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]) };
		
		sf::RectangleShape aux(dim);
		aux.setFillColor(c);
		aux.setPosition(pos);
		
		m_rectangles[i] = aux;
	}
}
void Menu::LoadSliders()
{
	FileManager s("figures.conf", "sliders of "+m_location);
	m_sliders.resize(stoi(s["size"]));
	sf::Color c = utils::getColor(s["color"]);
	float speed=stoi(s["speed"]);
	for (size_t i=0; i<m_sliders.size(); ++i) 
	{
		std::string key = "slid" + std::to_string(i) + "-"; 
		m_sliders[i].setSpeed(speed);
		m_sliders[i].setColor(c);
		
		sf::Vector2f dim = { win_width * stof(s[key+"w"]), win_height * stof(s[key+"h"]) };
		m_sliders[i].setSize(dim);
		
		sf::Vector2f pos = { win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]) };
		m_sliders[i].setPosition(pos);
		
		sf::Vector2f limits=
		{win_width*stof(s[key+"min"])+(m_rectangles[0].getGlobalBounds()).width,win_width*stof(s[key+"max"])};
		m_sliders[i].setLimits(limits);
		
		int max=stoi(s[key+"top-value"]);
		m_sliders[i].setTopValue(max);
		
		
	}
	
}
void Menu::RandomizeMyColor(unsigned const& text_position)
{
	utils::HSV col((frame_count*3)%361, 100, 100);
	
	m_texts[text_position].setFillColor(col.MakeRGB());
	++frame_count;
}

void Menu::HighlightCurrentOption()
{
	for (size_t i=m_Noptions.x; i<=m_Noptions.y; ++i)
		m_texts[i].setFillColor({150, 150, 150, 150});
	m_texts[m_Noptions.x+current_option].setFillColor({255, 255, 255});
	//esto sirve para dar el efecto de selecionar la opcion actual 
	//(basicamente oscurece todos los textos selecionables menos el actual)
}

void Menu::Move_Option_Up()
{
	--current_option;
	if (current_option < 0)
		current_option = m_Noptions.y-m_Noptions.x;
}
void Menu::Move_Option_Down()
{
	++current_option;
	if (current_option > m_Noptions.y-m_Noptions.x)
		current_option = 0;
}


