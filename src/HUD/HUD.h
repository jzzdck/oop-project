#ifndef HUD_H
#define HUD_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "Healthbar.h"
#include "Bar.h"
#include "../Entity/Player.h"
#include "AmmoBar.h"

class HUD {
public:
	HUD(const Player* target);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void DrawHUD(sf::RenderWindow &win, float zoom_level);
	void Update();
private:
	const Player* m_target;
	sf::Vector2f m_pos, m_relative_percentage;
	
	float m_dir;
	Bar m_playercolor;
	AmmoBar m_ammobar;
	HealthBar m_healthbar;
	
	sf::Sprite m_hud;
	sf::Texture m_texture;
};

#endif

