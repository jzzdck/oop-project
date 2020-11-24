#include "Player.h"

void Player::Update(World &m_world) {
	
	// sideway movement logic
	m_speed.x = 5;
	if (sf::Keyboard::isKeyPressed(m_right))
		m_sprite.move(m_speed.x, 0);
	if (sf::Keyboard::isKeyPressed(m_left))
		m_sprite.move(-m_speed.x, 0);
	
	// jump logic
	if (!m_world.CollidesWith(m_sprite))
		m_speed.y += m_world.GetGravity();
	else {
		// antes de dibujarlo, se mueve arriba del piso
		m_sprite.move(0, -m_speed.y);
		while(!m_world.CollidesWith(m_sprite))
			m_sprite.move(0, 1); // se mueve hasta que toque el piso
		
		m_speed.y = 0;
		m_jumpcount = 2;
	}
	
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
}

void Player::Draw(sf::RenderWindow & win) {
	win.draw(m_sprite);
}

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_player_index(player_index), 
	m_jumpcount(2), is_jumping(false)
{
	m_sprite.scale(2,2);
	
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
		break;
	default:
		m_sprite.setColor({0,0,0});
		m_left = sf::Keyboard::Key::J;
		m_right = sf::Keyboard::Key::L;
		break;
	}
}
