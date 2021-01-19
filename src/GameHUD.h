#ifndef GAMEHUD_H
#define GAMEHUD_H
#include <vector>
#include "HUD.h"
#include "Entity/Player.h"
using namespace std;

class GameHUD {
public:
	GameHUD();
	void Init(std::vector<Player*> players);
	void Draw(sf::RenderWindow &win, float zoom_level);
	void Update();
private:
	std::vector<HUD> m_playerHUDs;
};

#endif

