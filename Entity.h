#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Game.h"

// * Entity es la clase madre de cualquier (valga la redundancia) entidad   
//   en el juego. *
// * Hay dos tipos: MovilEntity, StaticEntity. *

class Entity {
public:
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow &win) = 0;
	Entity(std::string spritename, float initial_x, float initial_y);
protected:
	std::string m_spritename;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif

