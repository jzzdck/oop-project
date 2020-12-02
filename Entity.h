#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "World.h"
#include <vector>

// * Entity es la clase madre de cualquier (valga la redundancia) entidad   
//   en el juego. *

class World;
class Game;

class Entity {
public:
	virtual void Update(World &m_world) = 0; // las entidades se actualizan segun el mundo en el que estan
	virtual void Draw(sf::RenderWindow &win) = 0;
	bool CollidesWith(const Entity &another);
protected:
	sf::Vector2f m_speed;
	float m_topspeed;
	std::vector<sf::Texture> m_textures;
	sf::Sprite m_sprite;
};

#endif

