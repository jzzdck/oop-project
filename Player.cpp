#include "Player.h"
#include <iostream>

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_index(player_index), 
	m_jumpcount(2), is_jumping(false), current_sprite(0)
{
	m_textures.resize(2);
	m_textures[1].loadFromFile("res/frog_right.png");
	
	switch (m_index) {
	case 0:
		m_sprite.setColor({213,198,55});
		m_left = sf::Keyboard::Key::Left;
		m_right = sf::Keyboard::Key::Right;
		m_space = sf::Keyboard::Key::Up;
		break;
	case 1:
		m_sprite.setColor({55,144,213});
		m_left = sf::Keyboard::Key::A;
		m_right = sf::Keyboard::Key::D;
		m_space = sf::Keyboard::Key::W;
	default: 
		break;
	}
}

void Player::Update(World &world) {
	float topspeed = 8;
	
	// jump mechanic: a switch
	// if "on" -> jump. if "on" and then "off" -> jump less
	if (is_jumping != sf::Keyboard::isKeyPressed(m_space)) 
	{
		is_jumping = !(is_jumping);
		if (is_jumping && m_jumpcount > 0) {
			m_speed.y = -10;
			--m_jumpcount;
		} else if (m_speed.y < -2)
			m_speed.y = -2;
	}
	
	// lateral movement
	// if m_right is pressed -> go right, idem for left
	// current_sprite based on key pressed
	if (sf::Keyboard::isKeyPressed(m_right)) {
		m_sprite.move(m_speed.x, m_speed.y);
		current_sprite = 1;
	} else if (sf::Keyboard::isKeyPressed(m_left)) {
		m_sprite.move(-m_speed.x, m_speed.y);
		current_sprite = 0;
	} else m_sprite.move(0, m_speed.y);
	
	// basic x-axis acceleration, values may be tweaked
	if (sf::Keyboard::isKeyPressed(m_right) ||
		sf::Keyboard::isKeyPressed(m_left))
	{
		m_speed.x += 0.25;
		if (m_speed.x > topspeed)
			m_speed.x = topspeed;
	} else m_speed.x = 0.0;
	
	RespondCollisionWith(world);
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	win.draw(m_sprite);
}

void Player::RespondCollisionWith(World & world) {
	// floor collision
	if (world.FloorCollision(m_sprite)) {
		m_sprite.move(0, -m_speed.y);
		m_speed.y = 0;
		m_jumpcount = 2;
	} else m_speed.y += world.GetGravity();
	
	// wall collision
	int dir = world.WallCollision(m_sprite);
	if (dir) {
		while (world.WallCollision(m_sprite))
			m_sprite.move(dir, 0.35);
	}
}

