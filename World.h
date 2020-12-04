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
	void Draw(sf::RenderWindow &win);
	
	int CollidesWith(const sf::Sprite &entity);
	sf::Vector2<double> GetResponse(const sf::Sprite &entity, int index);
	float GetGravity() const { return m_gravity; }
	
	World(float wdt, float hgt, float gravity);
private:
	void LoadMap();
	
	std::vector<sf::RectangleShape> m_platforms; // el "piso" del mundo
	float m_gravity; // variable "global" que afecta a todas las entidades del "mundo"
	float win_width, win_height;
	sf::Color m_c;
};

#endif

