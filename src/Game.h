#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Utils/FileManager.h"

class Escena;

/** @brief The highest hierarchy level of the game.
		   The game class serves as a nexus for all the components in the game, 
		   making the game's code more organized.
**/

class Game {
public:
	/// @brief Execute the main loop: ProcessEvents() -> Update() -> Draw() -> repeat.
	void Run(); 
	
	/// @brief Process game's events.
	void ProcessEvents();
	
	/// @brief Update the game's state.
	/// In this function the game sets its current scene to another one, if necessary.
	void Update();
	
	/// @brief Draw the game's elements.
	void Draw();
	
	/// @brief Change the game's scene.
	/// @param new_scene Set the next scene to this.
	void SetScene(Escena *new_scene);
	
	/// @brief Close the game's window.
	void Close();
	
	/// @brief Construct a game with a given a width, height and name.
	Game(float width, float height, std::string window_name);
	~Game();
private:
	sf::RenderWindow m_window;
	Escena *m_current_scene;
	Escena *m_next_scene = nullptr;
	float win_width, win_height;
};

#endif

