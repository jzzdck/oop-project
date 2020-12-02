#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Settings.h"
#include <sstream>

Player::Player (float initial_x, float initial_y, int player_index) :
	m_index(player_index), m_jumpcount(2), 
	is_jumping(false), current_sprite(!player_index)
{
	m_sprite.setPosition(initial_x, initial_y);
	m_topspeed = 8;
	LoadTextures();
	LoadKeys();
}

void Player::Update(World &world) {
	// jump mechanic: a switch
	// if "on" -> jump. if "on" and then "off" -> jump less
	if (is_jumping != m_Input["jump"]) {
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
	
	if (m_Input["right"] || m_Input["left"]) {
		m_speed.x += 0.25;
		if (m_speed.x > m_topspeed)
			m_speed.x = m_topspeed;
	} else m_speed.x = 0.0;
	
	RespondCollisionWith(world);
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	ms_belly.setTexture(current_sprite ? mt_belly[1] : mt_belly[0]);
	ms_belly.setPosition(m_sprite.getPosition()); // belly postion relative to player;
	
	win.draw(ms_belly);
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
	if (dir) m_sprite.move(dir*m_speed.x, -m_speed.y);
}

void Player::LoadKeys()
{
	std::string keyword="controls=p"+std::to_string(m_index);
	Settings s("controls.conf",keyword);
	
	m_Input.BindKey("left", m_Input<s["key-left"]);
	m_Input.BindKey("right", m_Input<s["key-right"]);
	m_Input.BindKey("jump", m_Input<s["key-jump"]);
}

void Player::LoadTextures() {
	Settings s("textures.conf", "textures");
	
	std::stringstream ss;
	ss << s["color-p"+std::to_string(m_index)];
	int r, g, b;
	ss >> r >> g >> b;
	m_sprite.setColor(sf::Color(r, g, b));
	
	int bsize = stoi(s["belly-size"]);
	int psize = stoi(s["player-size"]);
	
	mt_belly.resize(bsize);
	for (size_t i=0; i<mt_belly.size(); ++i)
		mt_belly[i].loadFromFile(s["belly-texture"+std::to_string(i)] + ".png");
	
	m_textures.resize(psize);
	for (size_t i=0; i<m_textures.size(); ++i)
		m_textures[i].loadFromFile(s["player-texture"+std::to_string(i)] + ".png");
	
	// NOTA: no pongo la ruta a la carpeta porque cambiaria segun SO
}
