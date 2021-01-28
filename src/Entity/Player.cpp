#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"
#include <cmath>

Player::Player (sf::Vector2f pos, int player_index) :
	Entity(pos, "player"), 
	m_index(player_index),
	m_jump({2, -15}),
	m_animation(&m_sprite, &ms_belly)
{
	m_topspeed = 8.5f;
	
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
		if (e.key.code == m_input<="jump" && m_jump.count > 0) {
			m_animation.SetState(Animation::State::Jumping);
			m_speed.y = m_jump.speed;
			--m_jump.count;
		}
	} else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == m_input<="jump" && m_speed.y < -5)
			m_speed.y = -5;
	}
}

void Player::Update() {
	if (m_health.current_health <= 0.0f) {
		m_health.is_alive = false;
		return;
	}
	
	m_speed.x = std::fabs(m_speed.x);
	if (m_input["right"] || m_input["left"]) {
		m_animation.SetState(Animation::State::Running|m_animation.GetState());
		
		m_dir = 1.f;
		m_speed.x = std::min(m_speed.x + 0.7f, m_topspeed);
		
		if (m_input["left"])
			m_speed.x *= -1, m_dir = -1.f;
	} else {
		m_speed.x = 0.f;
		if (m_animation.GetState() != Animation::State::Jumping)
			m_animation.SetState(Animation::State::Idle);
	}
		
	if (m_platform) 
		m_sprite.move(m_platform->getSpeed());
	
	m_sprite.setTexture(m_textures[0], true);
	ms_belly.setTexture(m_textures[1], true);
	m_animation.Update();
	m_sprite.move(m_speed.x, m_speed.y);
}

void Player::Render() {
	if (!m_health.is_alive)
		return;
	
	RelocateSprites();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!m_health.is_alive) 
		return;
	
	target.draw(m_sprite,states);
	target.draw(ms_belly,states);	
}

void Player::RelocateSprites() {
	ms_belly.setPosition(m_sprite.getPosition());
	utils::flipTexture(m_dir, m_scale, ms_belly);
	utils::flipTexture(m_dir, m_scale, m_sprite);
}

void Player::ApplyResponse(const sf::Vector2f &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (vec.y) m_speed.y = 0;
	if (vec.y < 0 && m_speed.x)
		m_animation.SetState(Animation::State::Running);
	else if (!m_speed.x)
		m_animation.SetState(Animation::State::Idle);
	
	m_jump.count = 2;
}
