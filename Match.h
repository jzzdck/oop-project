#ifndef MATCH_H
#define MATCH_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Scene.h"
#include "Player.h"

class Match : public Escena {
public:
	~Match();
	Match(float width, float height);
	void Update (Game & g);
	void Draw (sf::RenderWindow & win);
private:
	std::vector<Entity*> m_players;
	/* 
	World* match_world; 
	capaz que un puntero a mundo para distintas rondas? 
	*/
};

#endif

