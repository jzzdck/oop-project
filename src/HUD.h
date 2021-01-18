#ifndef HUD_H
#define HUD_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Entity/Player.h"
#include <vector>

class HUD {
public:
	HUD(float dir, const sf::Vector2f &pos);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void SetPlayer(const Player* target);
	void Update();
private:
	const Player* m_target;
	sf::Vector2f m_pos;
	
	float prev_percentage, current_percentage, m_dir;
	std::vector<sf::RectangleShape> m_healthbar;
	// 0: current health, 1: previous health, 2: background
	
	sf::Sprite m_hud;
	sf::Texture m_texture;
	sf::RectangleShape m_playercolor;
};

#endif

