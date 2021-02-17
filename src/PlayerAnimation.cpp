#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(sf::Sprite * target, sf::Sprite * indep) {
	m_animations = {
		{target, indep, "running", {8, 0, 0.06f, {42.f, 50.f}}},
		{target, indep, "jump", {4, 0, 0.05f, {120.f/4.f, 50.f}}},
		{target, indep, "idle", {4, 0, 0.08f, {22.f, 50.f}}},
		{target, indep, "impact", {4, 0, 0.06f, {108.f/4.f, 45.f}}},
		{target, indep, "death", {4, 0, 0.15f, {248.f/4.f, 50.f}}}
	};
	
	m_animations.at(1).SetLoopability(false);
	m_animations.at(3).SetLoopability(false);
	m_animations.at(4).SetLoopability(false);
}

void PlayerAnimation::Update ( int current_state ) {
	if (previous != current_state && (previous == 3 or previous == 1))
		m_animations.at(previous).Reset();
	
	m_animations.at(current_state).Update();
	previous = current_state;
}

void PlayerAnimation::SetState (int new_state) {
	
}

