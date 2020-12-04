#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class Escena {
public:
	virtual void Update(Game &g) = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	Escena(float width, float height);
	virtual ~Escena() {};
protected:
	float win_width, win_height;
};

#endif

