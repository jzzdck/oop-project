#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

struct AnimationInfo {
	int frames;
	int current;
	float time_step;
	sf::Vector2f dims;
};

class Animation {
public:
	Animation(sf::Sprite* target, sf::Sprite *indep, std::string sprite_sheet, AnimationInfo info);
	void Update();
	void SetLoopability(bool looped) { loopable = looped; }
	void Reset() { m_info.current = 0; }
private:
	bool loopable = true;
	AnimationInfo m_info;
	sf::Clock m_clock;
	sf::Texture m_spritesheet;
	sf::Texture m_indeps;
	sf::Sprite* m_target;
	sf::Sprite* m_indep;
};

#endif

