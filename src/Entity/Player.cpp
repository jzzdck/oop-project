#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "../FileManager.h"
#include "../Utils/phutils.h"
#include <cmath>

Player::Player (sf::Vector2f pos, int player_index) :
	Entity(pos, "player"), 
	m_index(player_index),
	m_jumpcount(2),
	m_jumpspeed(-15), 
	is_jumping(false), 
	current_sprite(!player_index),
	can_grab(false)
{
	m_topspeed = 10.5f;
	
	LoadKeys();
	LoadBelly();
	m_sprite.setColor(utils::loadPlayerColor(m_index));
	m_sprite.scale(2,2);
	ms_belly.scale(2,2);
}

void Player::LoadKeys() {
	std::string keyword = "p"+std::to_string(m_index);
	FileManager s("controls.conf",keyword);
	
	std::vector<std::string> keys = {
		"left", "right", "jump", "down", "attack", "grab"
	};
	
	for (size_t i=0; i<keys.size(); ++i)
		m_input.BindKey(keys[i], m_input<s["key-" + keys[i]]);
}

void Player::LoadBelly() {
	FileManager s("textures.conf", "belly");
	int bsize = stoi(s["belly-size"]);
	
	mt_belly.resize(bsize);
	for (size_t i=0; i<mt_belly.size(); ++i)
		mt_belly[i].loadFromFile(s["belly-texture"+std::to_string(i)] + ".png");
}

void Player::Update() {
	if (is_jumping !=  m_input["jump"]) {
		is_jumping = !is_jumping;
		if (is_jumping && m_jumpcount > 0 ) {
			m_speed.y = m_jumpspeed;
			--m_jumpcount;
		} else if (m_speed.y < -5)
			m_speed.y = -5;
	}
	
	m_speed.x = std::fabs(m_speed.x);
	if (m_input["right"] || m_input["left"]) {
		current_sprite = 0;
		m_speed.x = std::min(m_speed.x + 0.7f, m_topspeed);
		
		if (m_input["left"])
			m_speed.x *= -1, current_sprite = 1;
		
		m_sprite.move(m_speed.x, 0);
	} else m_speed.x = 0.f;
	m_sprite.move(0, m_speed.y);
	
	if (m_weapon)
		m_weapon->SetAttacking(m_input["attack"]);
	
	set_grab = utils::wasPressed(can_grab, m_input["grab"]) ? can_grab : false;
	if (m_platform && !is_jumping) 
		m_sprite.move(m_platform->getSpeed());
}

void Player::Draw(sf::RenderWindow & win) {
	m_sprite.setTexture(m_textures[current_sprite]);
	ms_belly.setTexture(mt_belly[current_sprite]);
	
	ms_belly.setPosition(m_sprite.getPosition());
	if (m_item) m_item->GetSprite().setPosition(m_sprite.getPosition());
	
	win.draw(m_sprite);
	win.draw(ms_belly);
}

void Player::ApplyResponse(const sf::Vector2f &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (vec.y) m_speed.y = 0;
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
	m_item->SetSpeed({GetSpeed().x*1.3f, -6});
	m_item = nullptr;
}

void Player::UnassignObject(Weapon *if_weapon) {
	m_weapon->SetOwner(-1);
	m_weapon->SetSpeed({GetSpeed().x*1.3f, -6.f});
	m_weapon->SetAttacking(false);
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
