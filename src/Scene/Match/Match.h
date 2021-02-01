#ifndef MATCH_H
#define MATCH_H
#include <vector>
#include "../Scene.h"
#include "../../Game.h"
#include "../../Graphics/Camera.h"
#include "../Menu/Menu_Pause.h"
#include "../../HUD/MatchHUD.h"
#include "../../EntitiesFacade/EntitiesFacade.h"
#include "MatchSettings.h"

/** @brief The Match class handles the connection between the elements of the game 
World, Player, Weapon, etc.
**/

class Match : public Scene {
public:
	void ProcessEvent(sf::Event& e,Game& g) override;
	void Update(Game & g);
	void Render(DrawingEnviroment& drawEnv)override;
	Match(MatchSettings m, float width, float height);
	~Match();
private:
	int CurrentRoundEnded(const std::vector<int> &round_state);
	void UpdateGameState(int someone_won, Game & g);
	
	MatchSettings m_settings;
	MatchHUD m_gamehud; 
	EntitiesFacade m_entities;
	sf::Clock m_gameclock;
	
	Camera m_camera;
	bool m_pause;
	
	Menu_Pause m_pmenu;
};

#endif

