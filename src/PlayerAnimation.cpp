#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(sf::Sprite * target, sf::Sprite * indep) :
	previous(0)
{
	m_animations = {
		{target, indep, "jump", {3, 0, 1.f, {120.f/4.f, 49.f}}},
		{target, indep, "impact", {4, 0, 0.07f, {108.f/4.f, 45.f}}},
		{target, indep, "death", {4, 0, 0.08f, {248.f/4.f, 50.f}}},
		{target, indep, "running", {8, 0, 0.06f, {42.f, 50.f}}},
		{target, indep, "idle", {4, 0, 0.08f, {22.f, 50.f}}}
	};
	
	for (int i=0; i<3; ++i) 
		m_animations.at(i).loopable = false;
	m_animations.at(1).interruptable = false;
}

void PlayerAnimation::Update ( int current_state ) {
	auto &previous_anim = m_animations.at(previous);
	
	bool special = !previous_anim.interruptable || !previous_anim.loopable;
	if (previous_anim.interruptable || previous_anim.IsFinished()) {
 		m_animations.at(current_state).Update();
		if (previous != current_state && special) 
			previous_anim.Reset();
		previous = current_state;
	} else previous_anim.Update();
}
