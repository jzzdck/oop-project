#ifndef HUD_H
#define HUD_H

class HUD {
public:
	HUD();
	void Draw(sf::RenderWindow &win);
	void SetPlayers(std::vector<Player*> m_players);
	void SetCenter(sf::Vector2f &center);
	void Update();
private:
	float prev_percentage, current_percentage;
	sf::RectangleShape m_healthbar;
	sf::RectangleShape m_hud;
	sf::RectangleShape m_playercolor;
	sf::Vector2f *m_center;
	sf::Texture m_texture;
};

#endif

