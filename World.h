#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>

class Entity;

class World {
public:
	World(float wdt, float hgt, float gravity);
	void Draw(sf::RenderWindow &win);
	int FloorCollision(sf::Sprite &this_one);
	int WallCollision(sf::Sprite &this_one);
	float GetGravity() { return m_gravity; }
private:
	std::vector<bool> is_floor;
	std::vector<sf::RectangleShape> m_platforms; // el "piso" del mundo
	float m_gravity; // variable "global" que afecta a todas las entidades del "mundo"
	float win_width, win_height;
};

#endif

