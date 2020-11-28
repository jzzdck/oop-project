#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Entity.h"

class Game;

class Player : public Entity {
public:
	void Update(World &world) override;
	void Draw(sf::RenderWindow &win) override;
	int GetIndex() const { return m_player_index; }
	Player(std::string spritename, float initial_x, float initial_y, int player_index);
private:
	void RespondCollision(World &world);
	sf::Keyboard::Key m_right, m_left, m_space;
	int m_player_index, m_jumpcount;
	float m_slidespeed;
	bool is_jumping, can_move;
};

#endif

