#ifndef MATCHHUD_H
#define MATCHHUD_H
#include <vector>
#include "HUD.h"
#include "Entity/Player.h"
using namespace std;

class MatchHUD {
public:
	MatchHUD();
	void SetPlayers(std::vector<Player*> players);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void Update();
private:
	std::vector<HUD> m_playerHUDs;
};

#endif

