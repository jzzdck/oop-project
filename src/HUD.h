#ifndef HUD_H
#define HUD_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Entity/Player.h"
#include <vector>
#include "Healthbar.h"
#include "Bar.h"

class HUD {
public:
	HUD(const Player* target);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void DrawHUD(sf::RenderWindow &win, float zoom_level);
	void DrawPlayerColor(sf::RenderWindow &win, float zoom_level);
	void SetPlayer(const Player* target);
	void Update();
private:
	const Player* m_target;
	sf::Vector2f m_pos, m_relative_percentage;
	
	float m_dir;
	HealthBar m_healthbar;
	Bar m_playercolor;
	
	sf::Sprite m_hud;
	sf::Texture m_texture;
};

#endif

