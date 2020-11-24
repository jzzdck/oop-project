#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class Escena {
public:
	Escena(float width, float height);
	virtual void Update(Game &g) = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
protected:
	float win_width, win_height;
};

#endif

