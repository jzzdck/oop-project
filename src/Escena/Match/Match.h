#ifndef MATCH_H
#define MATCH_H
#include <vector>
#include "World.h"
#include "../Scene.h"
#include "../../Game.h"
#include "../../Graphics/Camera.h"
#include "../../Entity/EntitiesFacade.h"
#include "../Menu/Menu_Pause.h"
#include "../../MatchHUD.h"

/** @brief The Match class handles the connection between the elements of the game 
World, Player, Weapon, etc.
**/

class Match : public Escena {
public:
	void ProcessEvent(sf::Event& e,Game& g) override;
	void Update(Game & g);
	void Draw(sf::RenderWindow & win);
	Match(float width, float height);
	~Match();
private:
	MatchHUD m_gamehud; 
	EntitiesFacade m_entities;
	Camera m_camera;
	bool m_pause;
	
	Menu_Pause m_pmenu;
};

#endif

