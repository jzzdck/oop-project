#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include "Entity.h"
#include "../Utils/Controls.h"
#include "../Game.h"
#include "../Graphics/Animation.h"

struct Jump {
	int count;
	int speed;
};

struct HealthData {
	float max_health = 1000.f;
	float current_health = 1000.f;
	bool is_alive = true;
};

/// @brief The Player class relates players' input to the game.
class Player : public Entity {
public:
	void ProcessEvents(sf::Event &e);
	void Update() override; 
	void Render() override;
	
	void Respawn();
	void ApplyResponse(const sf::Vector2f &vec) override;
	HealthData &GetHealthData() { return m_health; };
	HealthData  GetHealthData() const { return m_health; };
	int GetIndex() const { return m_index; }
	Controls &GetControls() { return m_input;}
	Player(sf::Vector2f pos, int player_index);
private:
	int m_index;
	Jump m_jump;
	Controls m_input;
	Animation m_animation;
	HealthData m_health;
	sf::Sprite ms_belly;
	float m_topspeed;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void LoadKeys();
};

#endif
