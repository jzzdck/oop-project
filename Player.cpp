#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Settings.h"

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_index(player_index), 
	m_jumpcount(2), is_jumping(false), current_sprite(0)
{
	m_textures.resize(2);
	m_textures[1].loadFromFile("res/frog_left.png");
	LoadPlayerConfig();
}

void Player::Update(World &world) {
	float topspeed = 8;
	
	// jump mechanic: a switch
	// if "on" -> jump. if "on" and then "off" -> jump less
	if (is_jumping != m_Input["jump"])
	{
		is_jumping = !(is_jumping);
		if (is_jumping && m_jumpcount > 0) {
			m_speed.y = -10;
			--m_jumpcount;
		} else if (m_speed.y < -2)
			m_speed.y = -2;
	}

	if (m_Input["right"]) {
		m_sprite.move(m_speed.x, m_speed.y);
		current_sprite = 0;
	} else if (m_Input["left"]) {
		m_sprite.move(-m_speed.x, m_speed.y);
		current_sprite = 1;
	} else m_sprite.move(0, m_speed.y);
	
	if ((m_Input["right"]) ||
		(m_Input["left"]))
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

void Player::LoadPlayerConfig()
{
	std::string keyword="player="+std::to_string(m_index);
	Settings s("player.conf",keyword);
	sf::Uint8 r,g,b,a;
	r=stoi(s["channel-r"]);
	g=stoi(s["channel-g"]);
	b=stoi(s["channel-b"]);
	a=stoi(s["channel-a"]);
	m_sprite.setColor({r,g,b,a});
	
	std::string str_key;
	
	str_key=s["key-left"];
	m_Input.BindKey("left",m_Input<str_key);
	
	str_key=s["key-right"];
	m_Input.BindKey("right",m_Input<str_key);
	
	str_key=s["key-jump"];
	m_Input.BindKey("jump",m_Input<str_key);
}
