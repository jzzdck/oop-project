#include "Player.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "../Utils/FileManager.h"
#include "../Utils/generalUtils.h"
#include <cmath>
#include <algorithm>
#include <SFML/Graphics/Shader.hpp>

Player::Player (sf::Vector2f pos, int player_index) :
	Entity(pos, "player"), 
	m_index(player_index),
	m_jump({2, -15}),
	m_animation(&m_sprite, &ms_belly)
{
	m_topspeed = 12.5f;
	
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

void Player::ProcessEvents (sf::Event & e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == m_input.GetKey("jump") && m_jump.count > 0) {
			m_animation.SetState(Animation::State::Jumping);
			m_speed.y = m_jump.speed;
			--m_jump.count;
		}
	} else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == m_input.GetKey("jump") && m_speed.y < -5)
			m_speed.y = -5;
	}
}

void Player::Update() {
	if (m_health.current_health <= 0.0f) {
		m_health.is_alive = false;
		return;
	}
	
	if (m_input["right"] or m_input["left"]) {
		m_dir = m_input["left"] ? -1.f : 1.f;
		m_animation.SetState(Animation::State::Running|m_animation.GetState());
		m_speed.x = std::clamp(m_speed.x, -m_topspeed, m_topspeed);
		m_accel += {m_dir*0.6f, 0.f};
	} else if (m_animation.GetState() != Animation::State::Jumping)
		m_animation.SetState(Animation::State::Idle);
	
	if (m_platform) 
		m_sprite.move(m_platform->GetSpeed());
	
	m_sprite.setTexture(m_textures[0], true);
	ms_belly.setTexture(m_textures[1], true);
	m_animation.Update();
	
	m_accel.x += -m_speed.x * 0.05f;
	Entity::Update();
}

void Player::Render() {
	if (!m_health.is_alive)
		return;
	
	ms_belly.setPosition(m_sprite.getPosition());
	utils::flipTexture(m_dir, m_scale, ms_belly);
	utils::flipTexture(m_dir, m_scale, m_sprite);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!m_health.is_alive) 
		return;
	
	target.draw(m_sprite,&s);
	target.draw(ms_belly,&s);	
}

void Player::ApplyResponse(const sf::Vector2f &vec) {
	m_sprite.move(vec.x, vec.y);
	
	if (vec.y) m_speed.y = 0;
	if (vec.y < 0 && m_speed.x)
		m_animation.SetState(Animation::State::Running);
	else if (!m_speed.x)
		m_animation.SetState(Animation::State::Idle);
	
	if (vec.y < 0) m_jump.count = 2;
}

void Player::Respawn ( ) {
	m_sprite.setPosition(GetInitPos());
	m_speed = m_accel = {0, 0};
	m_health.current_health = 1000.f;
	m_health.is_alive = true;
}

