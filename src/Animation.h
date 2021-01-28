#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Animation {
public:
	enum State {
		Idle    = 1 << 0, 
		Running = 1 << 1, 
		Jumping = 1 << 2
	};
	
	Animation(sf::Sprite* target, sf::Sprite *indep);
	void Update(State current_state);
private:
	void UpdateRun();
	
	sf::Clock m_clock;
	sf::Time time_per_frame;
	int run_frames = 8;
	int current_frame = 0;
	sf::Texture m_spritesheet;
	sf::Texture m_indeps;
	sf::Sprite* m_target;
	sf::Sprite* m_indep;
};


inline constexpr Animation::State operator|(Animation::State a, Animation::State b) {
	return static_cast<Animation::State>(static_cast<int>(a) |
										 static_cast<int>(b));
}

#endif

