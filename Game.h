#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Scene.h"
#include "Menu.h"
#include "Match.h"

class Escena;

class Game {
public:
	/// metodos
	void Run(); 
	void ProcessEvents(); // procesa la pila de eventos, eventos de juego como ganar una partida, cambiar de escena, etc
	void Update(); // actualiza todas las entidades y escenas, generalmente va la logica aca
	void Draw(); // las dibuja y muestra en ventana, no deberia haber mucho aca
	void SetScene(Escena *new_scene); // setea la escena actual 
	void Close();
	
	// constructores/destructores
	Game(float width, float height, std::string window_name);
	~Game();
private:
	sf::RenderWindow m_window;
	Escena *m_current_scene;
	Escena *m_next_scene = nullptr;
	
	float win_width, win_height;
};

#endif

