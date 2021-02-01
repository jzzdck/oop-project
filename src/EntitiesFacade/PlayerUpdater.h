#ifndef PLAYERUPDATER_H
#define PLAYERUPDATER_H
#include "EntityArray.h"

class PlayerUpdater : public EntityArray {
public:
	PlayerUpdater(const sf::Vector2f &winsize);
	void UpdateRegardingTo (PlayerInfo &info, Player * player, World &world) override;
	void RenderWith (DrawingEnviroment & drawEnv) override { return; };
	void ProcessPlayerEvents(PlayerInfo &info, Player* player, sf::Event &e) override;
	std::vector<PlayerInfo> UpdateArray(std::vector<PlayerInfo> &info, World &world) override {
		return info;
	};
	
private:
	std::vector<float> m_respawners;
	sf::Clock m_gameclock;
	
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override {};
	void SpawnRandom () override {};
};

#endif

