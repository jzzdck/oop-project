#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>

class Game;

/// @brief Mother class to all game's states.
/** Escena is the mother class to every other game state. A game state refers to
	all of the different "configurations" of the main window. A game state could be
	a match between	two players, the main menu, the options menu, etc. **/
class Escena {
public:
	virtual void ProcessEvent(sf::Event& e,Game& g)=0;
	virtual void Update(Game &g) = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	Escena(float width, float height);
	virtual ~Escena() {};
protected:
	float win_width, win_height;
};

#endif

