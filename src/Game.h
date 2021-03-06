#ifndef GAME_H
#define GAME_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Utils/FileManager.h"
#include "Graphics/DrawingEnviroment.h"

class Scene;

/** @brief The highest hierarchy level of the game.
		   The game class serves as a nexus for all the components in the game, 
		   making the game's code more organized.
**/

class Game {
public:
	/// @brief Execute the main loop: ProcessEvents() -> Update() -> Render() -> repeat.
	void Run(); 
	
	/// @brief Process game's events.
	void ProcessEvents();
	
	/// @brief Update the game's state.
	/// In this function the game sets its current scene to another one, if necessary.
	void Update();
	
	/// @brief Render the game's elements.
	void Render();
	
	/// @brief Change the game's scene.
	/// @param new_scene Set the next scene to this.
	void SetScene(Scene *new_scene);
	
	/// @brief Close the game's window.
	void Close();
	
	/// @brief Construct a game with a given a width, height and name.
	Game(float width, float height, std::string window_name);
	~Game();
private:
	sf::RenderWindow m_window;
	Scene *m_current_scene;
	Scene *m_next_scene = nullptr;
	float win_width, win_height;
	
	DrawingEnviroment m_drawEnv;
};

#endif

