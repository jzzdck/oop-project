#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "Controls.h"

class Game;

class Player : public Entity {
public:
	void Update(World &world) override;
	void Draw(sf::RenderWindow &win) override;
	int GetIndex() const { return m_index; }
	Player(std::string spritename, float initial_x, float initial_y, int player_index);
private:
	void RespondCollisionWith(World &world);
	Controls m_InputManager;
	int m_index, m_jumpcount;
	bool is_jumping, can_move;
};

#endif

