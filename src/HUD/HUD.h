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
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "../Graphics/DrawingEnviroment.h"
#include "../Entity/EntitiesFacade.h"

class HUD : public sf::Drawable {
public:
	HUD(int index);
	void Render(DrawingEnviroment &drawEnv, float zoom_level);
	void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
	void Update(const PlayerInfo &info);
private:
	sf::Vector2f m_pos, m_relative_percentage;
	
	float m_dir;
	Bar m_playercolor;
	AmmoBar m_ammobar;
	HealthBar m_healthbar;
	
	sf::Sprite m_hud;
	sf::Texture m_texture;
};

#endif

