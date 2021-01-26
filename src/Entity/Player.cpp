#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"
#include <cmath>

Player::Player (sf::Vector2f pos, int player_index) :
	Entity(pos, "player"), 
	m_index(player_index),
	m_jumpcount(2),
	m_jumpspeed(-15)
{
	m_topspeed = 10.5f;
	
	LoadKeys();
	m_sprite.setColor(utils::loadPlayerColor(m_index));
	ms_belly.setTexture(m_textures[1]);
	ms_belly.scale(m_dir*2,2);
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

void Player::ProcessEvents (sf::Event & e, Game & g) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == m_input<="jump" && m_jumpcount > 0) {
			m_speed.y = m_jumpspeed;
			--m_jumpcount;
		}
	} else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == m_input<="jump" && m_speed.y < -5)
			m_speed.y = -5;
	}
}

void Player::Update() {
	if (!IsAlive())
		return;
	
	m_speed.x = std::fabs(m_speed.x);
	if (m_input["right"] || m_input["left"]) {
		m_dir = 1.f;
		m_speed.x = std::min(m_speed.x + 0.7f, m_topspeed);
		
		if (m_input["left"])
			m_speed.x *= -1, m_dir = -1.f;
	} else m_speed.x = 0.f;
	
	if (m_weapon)
		m_weapon->SetAttacking(m_input["attack"]);
	
	if (m_platform) 
		m_sprite.move(m_platform->getSpeed());
	
	m_sprite.move(m_speed.x, m_speed.y);
	RelocateSprites();
}

void Player::Draw(sf::RenderWindow & win) {
	if (!IsAlive()) 
		return;
	
	ms_belly.setPosition(m_sprite.getPosition());
	utils::flipTexture(m_dir, m_scale, ms_belly);
	utils::flipTexture(m_dir, m_scale, m_sprite);
	
	if (m_item) 
		m_item->GetSprite().setPosition(m_sprite.getPosition());
	
	win.draw(m_sprite);
	win.draw(ms_belly);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	
	if (!IsAlive()) 
		return;
	
	target.draw(m_sprite);
	target.draw(ms_belly);

	
}
void Player::RelocateSprites()
{
	ms_belly.setPosition(m_sprite.getPosition());
	utils::flipTexture(m_dir, m_scale, ms_belly);
	utils::flipTexture(m_dir, m_scale, m_sprite);
	
	if (m_item) 
		m_item->GetSprite().setPosition(m_sprite.getPosition());

}

void Player::ApplyResponse(const sf::Vector2f &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (vec.y) m_speed.y = 0;
	m_jumpcount = 2;
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

void Player::UnassignObjects ( ) {
	if (m_weapon) 
		UnassignObject(m_weapon);
	
	if (m_item)
		UnassignObject(m_item);
}

sf::Vector2i Player::GetAmmo ( ) const {
	if (!m_weapon)
		return {-1, -1};
	else
		return m_weapon->GetAmmo();
}
