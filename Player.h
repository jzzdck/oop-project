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
	
	void ApplyGravity(float gravity);
	void ApplyResponse(const sf::Vector2<double> &vec);
	int GetJumpSpeed() const { return m_jumpspeed; }
	int GetIndex() const { return m_index; }
	
	Player(float initial_x, float initial_y, int player_index);
	~Player();
private:
	void LoadBelly();
	void LoadKeys();
	void LoadColor();
	void LoadRandomColor();
	
	Controls m_Input;
	int m_index, m_jumpcount, current_sprite;
	int m_jumpspeed;
	bool is_jumping;
	
	sf::Sprite ms_belly;
	std::vector<sf::Texture> mt_belly;
	Revolver m_weapon;
};

#endif

