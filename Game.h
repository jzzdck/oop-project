#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Scene.h"

class Escena;

class Game {
public:
	/// metodos
	/* 
	
	 * run es el loop principal de juego *
	 no es mas que una funcion "englobadora" que organiza el codigo. 
	 tener en cuenta que el verdadero trabajo de procesar eventos,
	 actualizar, y dibujar lo hacen los objetos especificos
	 que lo requieran, nunca/casi nunca la clase Juego 
	
	*/
	
	void Run(); 
	void ProcessEvents(); // procesa la pool de eventos
	void Update(); // actualiza todas las entidades y escenas
	void Draw(); // las dibuja y muestra en ventana
	void SetScene(Escena *new_scene); // setea la escena actual 
	
	// constructores/destructores
	Game(float width, float height, std::string window_name);
	~Game();
private:
	sf::RenderWindow m_window;
	Escena *m_current_scene;
	Escena *m_next_scene;
	
	float win_width, win_height;
};

#endif

