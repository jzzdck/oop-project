#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Settings.h"
#include <sstream>
#include "Revolver.h"
#include "World.h"

Player::Player (float initial_x, float initial_y, int player_index) :
	Entity("player"), m_index(player_index), m_jumpcount(2), 
	is_jumping(false), current_sprite(!player_index), 
	m_weapon(player_index, 49)
{
	m_sprite.setPosition(initial_x, initial_y);
	m_weapon.SetPos(m_sprite.getPosition(), current_sprite);
	m_topspeed = 8;
	
	LoadKeys();
	LoadBelly();
	LoadColor();
	LoadTextures();
}

void Player::Update() {
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
	
	if (m_Input["attack"]) m_weapon.Attack();
	m_weapon.SetPos(m_sprite.getPosition(), current_sprite);
	m_weapon.Update();
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	ms_belly.setTexture(current_sprite ? mt_belly[1] : mt_belly[0]);
	ms_belly.setPosition(m_sprite.getPosition()); // belly postion relative to player;
	
	m_weapon.Draw(win);
	win.draw(ms_belly);
	win.draw(m_sprite);
}

void Player::RespondFloorCollision() {
	m_sprite.move(0, -m_speed.y);
	m_speed.y = 0;
	m_jumpcount = 2;
}

void Player::RespondWallCollision(int dir) {
	m_sprite.move(dir*m_speed.x, 0);
}

void Player::ApplyForce(float fx, float fy) {
	m_speed.x += fx;
	m_speed.y += fy;
}

void Player::LoadKeys()
{
	std::string keyword="controls=p"+std::to_string(m_index);
	Settings s("controls.conf",keyword);
	
	m_Input.BindKey("left", m_Input<s["key-left"]);
	m_Input.BindKey("right", m_Input<s["key-right"]);
	m_Input.BindKey("jump", m_Input<s["key-jump"]);
	m_Input.BindKey("attack", m_Input<s["key-attack"]);
}

void Player::LoadBelly() {
	Settings s("textures.conf", "belly");
	int bsize = stoi(s["belly-size"]);

	mt_belly.resize(bsize);
	for (size_t i=0; i<mt_belly.size(); ++i)
		mt_belly[i].loadFromFile(s["belly-texture"+std::to_string(i)] + ".png");
}

void Player::LoadColor ( ) {
	int r, g, b;
	std::stringstream ss;
	Settings s("textures.conf", "player");
	
	ss << s["color-p"+std::to_string(m_index)];
	ss >> r >> g >> b;
	
	m_sprite.setColor(sf::Color(r, g, b));
}


Player::~Player ( ) {
	//	delete m_weapon;
}


