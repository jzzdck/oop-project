#include "Menu.h"
#include "Game.h"

Menu::Menu(float width, float height) : 
	Escena(width, height), frame_count(0), current_option(0), change_up(false), change_down(false)
{
	// 1* cargar la headlines en memoria
	std::ifstream fin("headlines.txt");
	std::vector<std::string> headlines; // no importa que se carguen tooodas, total despues del constructor se destruyen
	m_texts.resize(5);
	
	std::string aux;
	while (getline(fin, aux)) 
		headlines.push_back(aux);
	
	m_font.loadFromFile("Chava-Regular.ttf");
	m_texts[0].setFont(m_font);
	m_texts[0].setString("LOVIGAME");
	m_texts[0].setCharacterSize(110);
	m_texts[0].setFillColor({255, 255, 255});
	sf::FloatRect text_rect = m_texts[0].getLocalBounds();
	m_texts[0].setPosition((win_width-text_rect.width)/2,win_height/4); /// tratar de posicionar todo relativamente a las dimensiones de la ventana
	
	m_texts[1].setFont(m_font);
	m_texts[1].setString(headlines[rand() % headlines.size()]+"!"); // 2* elegir una al azar
	m_texts[1].setFillColor({255, 255, 255});
	m_texts[1].setCharacterSize(20);
	text_rect = m_texts[1].getLocalBounds();
	m_texts[1].setPosition((win_width-text_rect.width)/2, win_height/4 + win_height*0.17);
	
	std::vector<std::string> options = { "NEW GAME", "OPTIONS", "EXIT" };
	for (int i=0; i<3; ++i) { 
		m_texts[i+2].setFont(m_font);
		m_texts[i+2].setString(options[i]); // 2* elegir una al azar
		m_texts[i+2].setFillColor({150, 150, 150});
		m_texts[i+2].setCharacterSize(30);
		text_rect = m_texts[i+2].getLocalBounds();
		m_texts[i+2].setPosition((win_width-text_rect.width)/2, win_height*(0.56+0.12*i));
	}	
	
	m_texts[2].setFillColor({255,255,255});
}

void Menu::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		g.SetScene(new Match(win_width, win_height));
	
	if (change_down != sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		change_down = !(change_down);
		if (change_down) {
			++current_option;
			if (current_option >= 3)
				current_option %= 3;
		}
	}
	
	if (change_up != sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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
	if (frame_count > 8)  { 
		m_texts[1].setFillColor({r, g, b});
		frame_count = 0;
	}
	
	for (int i=0; i<3; ++i)
		m_texts[i+2].setFillColor({150, 150, 150, 150});
	m_texts[current_option+2].setFillColor({255, 255, 255});
	
	for(const auto &text : m_texts)
		win.draw(text);
	
	win.display();
}

