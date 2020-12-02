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
	Player(float initial_x, float initial_y, int player_index);
private:
	void RespondCollisionWith(World &world);
	void LoadKeys();
	void LoadTextures();
	
	Controls m_Input;
	int m_index, m_jumpcount, current_sprite;
	bool is_jumping;
	
	sf::Sprite ms_belly;
	std::vector<sf::Texture> mt_belly;
};

#endif

