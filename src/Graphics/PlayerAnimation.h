#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H
#include <vector>
#include "Animation.h"

class PlayerAnimation {
public:
	PlayerAnimation(sf::Sprite * target, sf::Sprite * indep);
	void Update(int current_state);
private:
	int previous;
	std::vector <Animation> m_animations;
};

#endif

