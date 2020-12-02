#ifndef MATCH_H
#define MATCH_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "Menu.h"
#include "Scene.h"
#include "Player.h"
#include "World.h"
#include <vector>

class Match : public Escena {
public:
	~Match();
	Match(float width, float height);
	void Update(Game & g);
	void Draw(sf::RenderWindow & win);
private:
	std::vector<Player> m_players;
	World m_world;
};

#endif

