#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "World.h"

// * Entity es la clase madre de cualquier (valga la redundancia) entidad   
//   en el juego. *

class World;
class Game;

class Entity {
public:
	virtual void Update(World &m_world) = 0; // las entidades se actualizan segun el mundo en el que estan
	virtual void Draw(sf::RenderWindow &win) = 0;
	sf::FloatRect GetGlobalBounds() const;
	sf::Vector2f GetSpeed() const { return m_speed; }
	void SetSpeed(float x, float y) { m_speed = {x, y}; }
	Entity(std::string spritename, float initial_x, float initial_y);
protected:
	std::string m_spritename;
	sf::Vector2f m_speed;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif

