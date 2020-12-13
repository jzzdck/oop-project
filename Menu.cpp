#include "Menu.h"
#include "Game.h"
#include <sstream>
#include "Settings.h"
#include "phutils.h"

Menu::Menu(float width, float height,std::string location) : 
	Escena(width, height),	frame_count(0),	current_option(0), 
	change_up(false), change_down(false),charge_select(true),
	m_player_selected(false),	m_location(location)
{
	LoadTexts();
	LoadKeys();
	if(m_location=="color-options")
	{
		m_cp0 = utils::loadPlayerColor(0);//El primer texto "color ;D" esta en pos =0
		m_cp1 = utils::loadPlayerColor(1);
//		LoadSliders(); 
	}
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
		if (str == "HEADLINE")
			str = LoadHeadline();
		if(str == "PLAYER")
			str+=" 1";
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

void Menu::Update (Game & g) {
	if (charge_select != m_input["select"]) {
		charge_select = !charge_select;
		if(charge_select)
		{
			if (m_location=="principal") 
			{
				switch (current_option) 
				{
				case 0:
					g.SetScene(new Match(win_width, win_height));
					break;
				case 1:
					g.SetScene(new Menu(win_width, win_height,"options"));
					break; // OptionMenu hereda de Menu
				
				case 2:
					g.Close();
					break;
				}
			}
			if (m_location=="options")
			{
				switch (current_option) 
				{
				case 0:
					g.SetScene(new Menu(win_width, win_height,"color-options"));
					break;
//				case 1:
//					g.SetScene(new Menu(win_width, win_height,"controls-options"));
//					break; 
					
				case 2:
					g.SetScene(new Menu(win_width,win_height,"principal"));
					break;
				}
			}
			if(m_location=="color-options")
			{
				switch (current_option) 
				{
				case 0:

					ChangePlayer();
					break;
//				case 1:
//					cambiar canal r
//					break; 
//				case 2:
//					cambiar canal g
//					break;
//				case 3:
//					cambiar canal b
//					break;
				case 4:
					g.SetScene(new Menu(win_width,win_height,"options"));
					break;
				}
			}
		}
	}
	
	if (change_down != m_input["go_down"]) {
		change_down = !(change_down);
		if (change_down) {
			++current_option;
			if (current_option >= m_Noptions)
				current_option %= m_Noptions;
		}
	}
	
	if (change_up != m_input["go_up"]) {
		change_up = !(change_up);
		if (change_up) {
			--current_option;
			if (current_option < 0)
				current_option = m_Noptions-1;
		}
	}
}

void Menu::Draw (sf::RenderWindow & win) {
	win.clear({0, 0, 0});
	
	if(m_location=="principal")
	{
		RandomizeMyColor(1);//el texto de headlines esta en la pos 1
	}
	if(m_location=="color-options")
	{
		CopyColorFromPlayer(0);//El primer texto "color ;D" esta en pos =0
	}
	HighlightCurrentOption();
	for(const auto &text : m_texts)
		win.draw(text);
	win.display();
}


std::string Menu::LoadHeadline() {
	std::ifstream fin("res/headlines.txt");
	std::vector<std::string> headlines;
	
	std::string aux;
	while (getline(fin, aux)) 
		headlines.push_back(aux);
	
	return headlines[rand() % headlines.size()]+"!";
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
	
//	sf::Uint8 r, g, b;
//	r = rand()%256;
//	g = rand()%256;
//	b = rand()%256;
//	
//	frame_count++;
//	if (frame_count % 8 == 0)
//		m_texts[text_position].setFillColor({r,g,b});
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

void Menu::CopyColorFromPlayer(unsigned const& text_position)
{
	if(!m_player_selected)
		m_texts[text_position].setFillColor(m_cp0);
	else
		m_texts[text_position].setFillColor(m_cp1);
}

void Menu::ChangePlayer()
{
	m_player_selected=!m_player_selected;
	std::string aux;
	aux=m_texts[1].getString();//usamos =1 porque ahi esta el texto de player
	aux.resize(aux.size()-1);//le sacomos ya sea el 1 o 2
	aux+=std::to_string(int(m_player_selected)+1);
	m_texts[1].setString(aux);
}

void Menu::LoadSliders()
{
	Settings s("figures.conf", "slider");
	m_slider.resize(stoi(s["size"]));
	
	sf::Color rect_color = utils::getColor(s["color"]);
	for (size_t i=0; i<m_slider.size(); ++i) { 
		std::string key = "rect" + std::to_string(i) + "-"; //recti-w, recti-h, etc
		sf::Vector2f dim = { win_width * stof(s[key+"w"]), win_height * stof(s[key+"h"]) };
		sf::Vector2f pos = {win_width * stof(s[key+"x"]), win_height * stof(s[key+"y"]) };
		
		sf::RectangleShape aux(dim);
		aux.setFillColor(rect_color);
		aux.setPosition(pos);
		m_slider[i] = aux;
	}
}
