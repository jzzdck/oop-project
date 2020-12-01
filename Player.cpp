#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_index(player_index), 
	m_jumpcount(2), is_jumping(false), can_move(true)
{
	m_sprite.scale(2, 2);
	m_speed = { 0.5, 0 };
	sf::Keyboard::Key right, left, jump;
	sf::Uint8 r,g,b;
	switch (m_index) {
	case 0:
		r=255;g=0;b=140;
		left = sf::Keyboard::Key::Left;
		right = sf::Keyboard::Key::Right;
		jump = sf::Keyboard::Key::Up;
		break;
	case 1:
		r=0;g=255;b=140;
		left = sf::Keyboard::Key::A;
		right = sf::Keyboard::Key::D;
		jump = sf::Keyboard::Key::W;
	default: 
		break;
	}
	m_sprite.setColor({r,g,b});
	m_InputManager.BindKey("left",left);
	m_InputManager.BindKey("right",right);
	m_InputManager.BindKey("jump",jump);
	
}

void Player::Update(World &world) {
	float topspeed = 8;
	
	if (is_jumping != m_InputManager.KeyState("jump")) 
	{
		is_jumping = !(is_jumping);
		if (is_jumping && m_jumpcount > 0) {
			m_speed.y = -10;
			--m_jumpcount;
		} else if (m_speed.y < -2)
			m_speed.y = -2;
	}
	
	if (m_InputManager.KeyState("right"))
		m_sprite.move(m_speed.x, m_speed.y);
	else if (m_InputManager.KeyState("left"))
		m_sprite.move(-m_speed.x, m_speed.y);
	else 
		m_sprite.move(0, m_speed.y);
	
	if (m_InputManager.KeyState("right") ||
		m_InputManager.KeyState("left"))
	{
		m_speed.x += 0.25;
		if (m_speed.x > topspeed)
			m_speed.x = topspeed;
	} else m_speed.x = 0.5;
	
	RespondCollisionWith(world);
}

void Player::Draw(sf::RenderWindow & win) {
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

