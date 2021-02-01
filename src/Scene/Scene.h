#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Graphics/DrawingEnviroment.h"

class Game;

/// @brief Mother class to all game's states.
/** Escena is the mother class to every other game state. A game state refers to
	all of the different "configurations" of the main window. A game state could be
	a match between	two players, the main menu, the options menu, etc. **/
class Scene {
public:
	virtual void ProcessEvent(sf::Event& e,Game& g)=0;
	virtual void Update(Game &g) = 0;
//	virtual void Render(sf::RenderWindow &win) = 0;
	virtual void Render(DrawingEnviroment& drawEnv) = 0;
	Scene(float width, float height);
	virtual ~Scene() {};
protected:
	float win_width, win_height;
};

#endif

