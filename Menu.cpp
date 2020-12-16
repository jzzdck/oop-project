#include "Menu.h"
#include <sstream>
#include "Settings.h"
#include "phutils.h"
#include "Game.h"
Menu::Menu(float width, float height,std::string location) : 
	Escena(width, height),	frame_count(0),	current_option(0), 
	change_up(false), change_down(false),
	change_right(false),change_left(false),
	charge_select(true),m_location(location),
	m_slide_speed(1,0)
	/*charge select tiene que estar inicializado con true, 
	para evitar que al pasar de una escena de menu a otra se selecione en el primer frame_count
	de la nueva escena la primera opcion.
	*/
{
	LoadTexts();
	LoadKeys();
}

void Menu::LoadTexts ( ) 
{
	Settings s("texts.conf",m_location);
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
	m_input.BindKey("go_right",m_input<s["key-right"]);
	m_input.BindKey("go_left",m_input<s["key-left"]);
}
void Menu::LoadSliders()
{
	Settings s("figures.conf", "sliders of "+m_location);
	m_sliders.resize(stoi(s["size"]));
	m_c = utils::getColor(s["color"]);
	for (size_t i=0; i<m_sliders.size(); ++i) {
		std::string key = "rect" + std::to_string(i) + "-"; //recti-w, recti-h, etc
		sf::Vector2f dim = { win_width * stof(s[key+"w"]), win_height * stof(s[key+"h"]) };
		sf::Vector2f pos = { win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]) };
		
		sf::RectangleShape aux(dim);
		aux.setPosition(pos);
		
		m_sliders[i] = aux;
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
	if (utils::wasPressed(change_up, m_input["go_up"])) {
		if (change_up) 
		{
			--current_option;
			if (current_option < 0)
				current_option = m_Noptions.y-m_Noptions.x;
		}
	}
}

void Menu::Move_Option_Down()
{
	if (utils::wasPressed(change_down, m_input["go_down"])) 
	{
		if (change_down)
		{
			++current_option;
			if (current_option > m_Noptions.y-m_Noptions.x)
				current_option = 0;
		}
	}
}

void Menu::Move_MySlider(unsigned const slider_index,bool const direction)
{
	if(direction)m_sliders[slider_index].move(m_slide_speed.x,m_slide_speed.y);
	else m_sliders[slider_index].move(-m_slide_speed.x,m_slide_speed.y);
	
}
