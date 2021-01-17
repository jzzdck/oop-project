#ifndef MATCH_H
#define MATCH_H
#include <vector>
#include "World.h"
#include "../Scene.h"
#include "../../Game.h"
#include "../../EntitiesFacade.h"
#include "../../Camera.h"

/** @brief The Match class handles the connection between the elements of the game 
World, Player, Weapon, etc.
**/

class Match : public Escena {
public:
	void ProcessEvent(sf::Event& e,Game& g)override;
	void Update(Game & g);
	void UpdateCamera();
	void Draw(sf::RenderWindow & win);
	Match(float width, float height);
	~Match();
private:
	EntitiesFacade m_entities;
	Camera m_camera;
	bool m_pause;
};

#endif

