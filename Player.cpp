#include "Player.h"

void Player::Update() {
	if (sf::Keyboard::isKeyPressed(m_right))
		m_sprite.move(5,0);
	if (sf::Keyboard::isKeyPressed(m_left))
		m_sprite.move(-5,0);
	
	// se compara el estado actual de la tecla m_space
	// con su respectivo estado previo, is_jumping. *el estado previo es el opuesto de isKeyPressed*
	// si son distintos, significa que se apreto la tecla o que se solto
	// si al ser distintos is_jumping se seteo a verdadero, se empieza a saltar
	if (is_jumping != sf::Keyboard::isKeyPressed(m_space)) 
	{
		is_jumping = !(is_jumping);
		if (is_jumping)
			m_sprite.move(0,-10);
	}
}

void Player::Draw(sf::RenderWindow & win) {
	win.draw(m_sprite);
}

Player::Player (std::string spritename, float initial_x, float initial_y, int player_index) :
	Entity(spritename, initial_x, initial_y), m_player_index(player_index)
{
	m_sprite.scale(2,2);
	is_jumping = false;
	
	switch(m_player_index) {
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
