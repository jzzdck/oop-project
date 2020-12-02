#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Scene.h"
#include "Menu.h"
#include "Match.h"
#include "Settings.h"

class Escena;

class Game {
public:
	void Run(); 
	void ProcessEvents();
	void Update();
	void Draw();
	void SetScene(Escena *new_scene);  
	void Close();
	
	Game(float width, float height, std::string window_name);
	~Game();
private:
	sf::RenderWindow m_window;
	Escena *m_current_scene;
	Escena *m_next_scene = nullptr;
	float win_width, win_height;
};

#endif

