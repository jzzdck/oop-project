#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "Controls.h"
#include "Weapon.h"
#include "Revolver.h"

class Game;

class Player : public Entity {
public:
	void Update() override;
	void Draw(sf::RenderWindow &win) override;
	
	void RespondFloorCollision();
	void RespondWallCollision(int dir);
	void ApplyForce(float fx, float fy);
	int GetIndex() const { return m_index; }
	
	Player(float initial_x, float initial_y, int player_index);
	~Player();
private:
	void LoadConfig();
	void LoadBelly();
	void LoadKeys();
	void LoadColor();
	
	Controls m_Input;
	int m_index, m_jumpcount, current_sprite;
	bool is_jumping;
	
	sf::Sprite ms_belly;
	std::vector<sf::Texture> mt_belly;
	
	Revolver m_weapon;
};

#endif

