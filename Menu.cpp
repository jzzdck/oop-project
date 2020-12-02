#include "Menu.h"
#include "Game.h"
#include <sstream>
#include "Settings.h"

Menu::Menu(float width, float height,unsigned IndexMenu) : 
	Escena(width, height),	frame_count(0),	current_option(0), 
	change_up(false), change_down(false),
	m_IndexMenu(IndexMenu)
{
	LoadTexts();
	LoadKeys();
}

void Menu::LoadTexts ( ) {
	Settings s("menu.conf", "texts");
	m_font.loadFromFile(s["font"] + ".ttf");
	m_texts.resize( stoi(s["size"]) );
	
	int r, g, b;
	std::stringstream ss;
	for (size_t i=0; i<m_texts.size(); ++i) { 
		m_texts[i].setFont(m_font);
		
		std::string key = "str" + std::to_string(i) + "-";
		std::string str = s[key+"set"];
		if (str == "HEADLINE")
			str = LoadHeadline();
		
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
	if (m_input["select"]) {
		switch (current_option) {
		case 0:
			g.SetScene(new Match(win_width, win_height));
			break;
//		case 1:
//			g.SetScene(new Menu(win_width, win_height,1));
//			break; // OptionMenu hereda de Menu
//		
		case 2:
			g.Close();
			break;
		}
	}
	
	if (change_down != m_input["go_down"]) {
		change_down = !(change_down);
		if (change_down) {
			++current_option;
			if (current_option >= 3)
				current_option %= 3;
		}
	}
	
	if (change_up != m_input["go_up"]) {
		change_up = !(change_up);
		if (change_up) {
			--current_option;
			if (current_option < 0)
				current_option = 3 + current_option;
		}
	}
}

void Menu::Draw (sf::RenderWindow & win) {
	win.clear({0, 0, 0});
	
	sf::Uint8 r, g, b;
	r = rand()%256;
	g = rand()%256;
	b = rand()%256;
	
	frame_count++;
	if (frame_count % 8 == 0) 
		m_texts[1].setFillColor({r, g, b});
	
	for (int i=0; i<3; ++i)
		m_texts[i+2].setFillColor({150, 150, 150, 150});
	m_texts[current_option+2].setFillColor({255, 255, 255});
	
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
	Settings s("controls.conf","controls=menu");
	m_input.BindKey("go_up",m_input<s["key-up"]);
	m_input.BindKey("go_down",m_input<s["key-down"]);
	m_input.BindKey("select",m_input<s["key-select"]);
}
