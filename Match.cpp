#include "Match.h"
#include "Menu.h"

Match::Match(float width, float height) :
	Escena(width, height)
{
	m_players.resize(2);
	m_players[0] = new Player("square.png", win_width-100, -20 + win_height/2, 0);
	m_players[1] = new Player("square.png", 100, -20 + win_height/2, 1);
}

void Match::Update (Game & g) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		g.SetScene(new Menu(win_width, win_height));
	
	for(auto &player : m_players) 
		player->Update();
}

void Match::Draw (sf::RenderWindow & win) {
	win.clear({158, 207, 222});
	for(auto &player : m_players) 
		player->Draw(win);
	
	/*
	
	 Esto de aca es un piso falso, solamente parece que funciona porque
	 esta dibujado debajo de donde estan posicionados los jugadores al principio,
	 habria que implementar una clase World que pertenezca al Match
	 y maneje todas las entidades del escenario.
	 World tambien debe tener parametros como gravedad.
	
	*/
	
	sf::RectangleShape rectangle(sf::Vector2f(win_width, win_height/2));
	rectangle.setFillColor({113, 189, 83});
	rectangle.setPosition(sf::Vector2f(0, win_height/2));
	win.draw(rectangle);
	
	win.display();
}

Match::~Match() {
	for (size_t i=0; i<m_players.size(); ++i) 
		delete m_players[i];
}

