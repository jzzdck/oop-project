#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Animation {
public:
	Animation(sf::Sprite* target, sf::Sprite *indep);
	void Update(const sf::Vector2f &m_speed);
private:
	sf::Clock m_clock;
	sf::Time time_per_frame;
	int run_frames = 8;
	int current_frame = 0;
	sf::Texture m_spritesheet;
	sf::Texture m_indeps;
	sf::Sprite* m_target;
	sf::Sprite* m_indep;
};

#endif

