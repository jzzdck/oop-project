#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "Settings.h"
#include "Revolver.h"
#include "World.h"
#include "phutils.h"

Player::Player (float initial_x, float initial_y, int player_index) :
	Entity("player"), m_index(player_index),
	m_jumpcount(2), m_jumpspeed(-12), is_jumping(false), 
	current_sprite(!player_index), 
	m_weapon(nullptr), m_item(nullptr), can_grab(false)
{
	m_sprite.setPosition(initial_x, initial_y);
	m_topspeed = 9.6;
	
	LoadKeys();
	LoadBelly();
	m_sprite.setColor(utils::loadPlayerColor(m_index));
}

void Player::Update() {
	if (is_jumping != m_Input["jump"]) {
		is_jumping = !(is_jumping);
		if (is_jumping && m_jumpcount > 0 ) {
			m_speed.y = m_jumpspeed;
			--m_jumpcount;
		} else if (m_speed.y < -5)
			m_speed.y = -5;
	}

	if (m_Input["right"]) {
		m_sprite.move(m_speed.x, 0);
		current_sprite = 0;
	} else if (m_Input["left"]) {
		m_sprite.move(-m_speed.x, 0);
		current_sprite = 1;
	} m_sprite.move(0, m_speed.y);
	
	if (m_Input["right"] || m_Input["left"]) {
		m_speed.x += 1;
		if (m_speed.x > m_topspeed)
			m_speed.x = m_topspeed;
	} else m_speed.x = 0.0;
	
	if (m_Input["attack"] && m_weapon) 
		m_weapon->Attack();
	
	if (can_grab != m_Input["grab"]) 
		can_grab = !can_grab;
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	ms_belly.setTexture(current_sprite ? mt_belly[1] : mt_belly[0]);
	ms_belly.setPosition(m_sprite.getPosition()); // belly postion relative to player;
	
	win.draw(ms_belly);
	win.draw(m_sprite);
}

void Player::ApplyResponse(const sf::Vector2<double> &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (!vec.x) 
		m_speed.y = 0, m_jumpcount = 2;
	else
		m_jumpcount = 2;
}

void Player::ApplyGravity(float gravity) {
	m_speed.y += gravity;
}

void Player::LoadKeys()
{
	std::string keyword="p"+std::to_string(m_index);
	Settings s("controls.conf",keyword);
	
	m_Input.BindKey("left", m_Input<s["key-left"]);
	m_Input.BindKey("right", m_Input<s["key-right"]);
	m_Input.BindKey("jump", m_Input<s["key-jump"]);
	m_Input.BindKey("attack", m_Input<s["key-attack"]);
	m_Input.BindKey("grab", m_Input<s["key-grab"]);
}

void Player::LoadBelly() {
	Settings s("textures.conf", "belly");
	int bsize = stoi(s["belly-size"]);

	mt_belly.resize(bsize);
	for (size_t i=0; i<mt_belly.size(); ++i)
		mt_belly[i].loadFromFile(s["belly-texture"+std::to_string(i)] + ".png");
}
