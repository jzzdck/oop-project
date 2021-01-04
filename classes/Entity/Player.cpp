#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "../FileManager.h"
#include "../Utils/phutils.h"

Player::Player (sf::Vector2f pos, int player_index) :
	Entity(pos, "player"), 
	m_index(player_index),
	m_jumpcount(1000),
	m_jumpspeed(-12), 
	is_jumping(false), 
	current_sprite(!player_index), 
	m_weapon(nullptr), 
	m_item(nullptr), 
	can_grab(false)
{
	m_topspeed = 9.6;
	
	LoadKeys();
	LoadBelly();
	m_sprite.setColor(utils::loadPlayerColor(m_index));
}

void Player::LoadKeys() {
	std::string keyword = "p"+std::to_string(m_index);
	FileManager s("controls.conf",keyword);
	
	m_input.BindKey("left", m_input<s["key-left"]);
	m_input.BindKey("right", m_input<s["key-right"]);
	m_input.BindKey("jump", m_input<s["key-jump"]);
	m_input.BindKey("attack", m_input<s["key-attack"]);
	m_input.BindKey("grab", m_input<s["key-grab"]);
}

void Player::LoadBelly() {
	FileManager s("textures.conf", "belly");
	int bsize = stoi(s["belly-size"]);
	
	mt_belly.resize(bsize);
	for (size_t i=0; i<mt_belly.size(); ++i)
		mt_belly[i].loadFromFile(s["belly-texture"+std::to_string(i)] + ".png");
}

void Player::Update() {
	if (utils::wasPressed(is_jumping, m_input["jump"])) {
		if (is_jumping && m_jumpcount > 0 ) {
			m_speed.y = m_jumpspeed;
			--m_jumpcount;
		} else if (m_speed.y < -5)
			m_speed.y = -5;
	}

	if (m_input["right"]) {
		m_sprite.move(m_speed.x, 0);
		current_sprite = 0;
	} else if (m_input["left"]) {
		m_sprite.move(-m_speed.x, 0);
		current_sprite = 1;
	} m_sprite.move(0, m_speed.y);
	
	if (m_input["right"] || m_input["left"]) {
		m_speed.x += 1;
		if (m_speed.x > m_topspeed)
			m_speed.x = m_topspeed;
	} else m_speed.x = 0.0;
	
	if (m_input["attack"] && m_weapon) 
		m_weapon->Action();
	
	if (utils::wasPressed(can_grab, m_input["grab"]))
		set_grab = can_grab;
	else 
		set_grab = false;
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	ms_belly.setTexture(current_sprite ? mt_belly[1] : mt_belly[0]);
	ms_belly.setPosition(m_sprite.getPosition());
	if (m_item) m_item->GetSprite().setPosition(m_sprite.getPosition());
	if (m_weapon) m_weapon->GetSprite().setPosition(m_sprite.getPosition());
	
	win.draw(ms_belly);
	win.draw(m_sprite);
}

void Player::ApplyResponse(const sf::Vector2f &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (!vec.x) 
		m_speed.y = 0, m_jumpcount = 2;
	else
		m_jumpcount = 2;
}

bool Player::PressedGrab (Item * if_item) {
	return set_grab && m_input["down"];
}

bool Player::PressedGrab (Weapon * if_weapon) {
	return set_grab && !m_input["down"];
}

void Player::UnassignObject (Item * if_item) {
	m_item->SetOwner(-1);
	m_item = nullptr;
}

void Player::UnassignObject(Weapon *if_weapon) {
	m_weapon->SetOwner(-1);
	m_weapon = nullptr;
}

void Player::AssignObject(Item *new_item) {
	if (m_item) 
		UnassignObject(m_item);
	
	m_item = new_item;
	m_item->SetOwner(m_index);
}

void Player::AssignObject(Weapon *new_weapon) {
	if (m_weapon) 
		UnassignObject(m_weapon);
	
	m_weapon = new_weapon;
	m_weapon->SetOwner(m_index);
}
