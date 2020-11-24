#include "Menu.h"
#include "Match.h"
using namespace std;

Menu::Menu(float width, float height) : Escena(width, height), frame_count(0) {
	// 1* cargar la headlines en memoria
	std::ifstream fin("headlines.txt");
	std::vector<std::string> headlines; // no importa que se carguen tooodas, total despues del constructor se destruyen
	
	std::string aux;
	while (getline(fin, aux)) 
		headlines.push_back(aux);
	
	m_font.loadFromFile("LucidaTypewriterBold.ttf");
	m_text1.setFont(m_font);
	m_text1.setString("LOVIGAME");
	m_text1.setCharacterSize(110);
	m_text1.setFillColor({255, 255, 255});
	sf::FloatRect text_rect = m_text1.getLocalBounds();
	m_text1.setPosition((win_width-text_rect.width)/2,win_height/4);
	
	m_text2.setFont(m_font);
	m_text2.setString(headlines[rand() % headlines.size()]+"!"); // 2* elegir una al azar
	m_text2.setFillColor({0, 0, 0});
	m_text2.setCharacterSize(20);
	text_rect = m_text2.getLocalBounds();
	m_text2.setPosition((win_width-text_rect.width)/2, win_height/4 + win_height*0.2);
}

void Menu::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		g.SetScene(new Match(win_width, win_height));
}

void Menu::Draw (sf::RenderWindow & win) {
	win.clear({0, 0, 0});
	win.draw(m_text1);
	
	sf::Uint8 r, g, b;
	r = rand()%256;
	g = rand()%256;
	b = rand()%256;
	
	frame_count++;
	if (frame_count > 6)  { 
		m_text2.setFillColor({r, g, b});
		frame_count = 0;
	}
	
	win.draw(m_text2);
	win.display();
}

