#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <vector>
#include "Settings.h"
#include "Player.h"

class Player;

class World {
public:
	World(float wdt, float hgt, float gravity);
	void Draw(sf::RenderWindow &win);
	int FloorCollision(const sf::Sprite &entity) const;
	int WallCollision(const sf::Sprite &entity) const;
	float GetGravity() const { return m_gravity; }
private:
	void LoadMap();
	
	std::vector<sf::RectangleShape> m_platforms; // el "piso" del mundo
	float m_gravity; // variable "global" que afecta a todas las entidades del "mundo"
	float win_width, win_height;
};

#endif

