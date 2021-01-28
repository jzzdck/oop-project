#ifndef PLAYERUPDATER_H
#define PLAYERUPDATER_H
#include "EntityArray.h"

class PlayerUpdater : public EntityArray {
public:
	PlayerUpdater(const sf::Vector2f &winsize);
	void UpdateRegardingTo (Player * player, World &world) override;
	void RenderWith (DrawingEnviroment & drawEnv) override { return; };
	void ProcessPlayerEvents(Player* player, sf::Event &e, Game &g) override;
private:
	std::vector<float> m_respawners;
	sf::Clock m_gameclock;
	
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override {};
	void SpawnRandom (const sf::Vector2f & pos) override {};
};

#endif

