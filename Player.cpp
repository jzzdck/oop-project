#include "Player.h"
#include <iomanip>
#include <iostream>

void Player::Update(World &world) {
	// sideway movement logic
	m_speed.x = can_move ? 5 : 0;	
	if (sf::Keyboard::isKeyPressed(m_right))
		m_sprite.move(m_speed.x, 0);
	if (sf::Keyboard::isKeyPressed(m_left))
		m_sprite.move(-m_speed.x, 0);
	
	// jump logic
	if (is_jumping != sf::Keyboard::isKeyPressed(m_space)) 
	{
		is_jumping = !(is_jumping);
		if (is_jumping && m_jumpcount > 0) {
			m_speed.y = -10;
			--m_jumpcount;
		} else if (m_speed.y < -2) 
			m_speed.y = -2;
	}
	
	m_sprite.move(0, m_speed.y);
	RespondCollision(world);
}

void Player::Draw(sf::RenderWindow & win) {
	win.draw(m_sprite);
}

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_player_index(player_index), 
	m_jumpcount(2), is_jumping(false), can_move(true), m_slidespeed(1)
{
	m_sprite.scale(2, 2);
	
	switch (m_player_index) {
	case 0:
		m_sprite.setColor({255,0,140});
		m_left = sf::Keyboard::Key::Left;
		m_right = sf::Keyboard::Key::Right;
		m_space = sf::Keyboard::Key::Space;
		break;
	case 1:
		m_sprite.setColor({0,255,140});
		m_left = sf::Keyboard::Key::A;
		m_right = sf::Keyboard::Key::D;
		m_space = sf::Keyboard::Key::B;
	default: 
		break;
	}
}

void Player::RespondCollision(World & world) {
	// floor collision
	switch (world.FloorCollision(m_sprite)) {
	case 0: 
		// no collision, is in air
		m_speed.y += world.GetGravity();
		break;
	case 1:
		// floor collision
		m_sprite.move(0, -m_speed.y);
		while (!world.FloorCollision(m_sprite))
			m_sprite.move(0, 1);
		
		m_slidespeed = 1;
		m_speed.y = 0;
		m_jumpcount = 2;
		break;
	case 2: 
		// ceiling collision
		m_sprite.move(0, -m_speed.y);
		m_speed.y = 0;
		break;
	}
	
	// wall collision
	int dir = world.WallCollision(m_sprite);
	if (dir) {
		can_move = false;
		while (world.WallCollision(m_sprite))
			m_sprite.move(dir, 0);
		
		m_sprite.move(0, m_slidespeed);
		m_slidespeed += world.GetGravity();
	} else can_move = true;
}

