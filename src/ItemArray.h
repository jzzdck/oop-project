#ifndef ITEMARRAY_H
#define ITEMARRAY_H
#include "EntityArray.h"
#include <vector>
#include "Entity/Item/Item.h"
#include "PlayerInfo.h"

class ItemArray : public EntityArray {
public:
	ItemArray(const sf::Vector2f &winsize);
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override;
	void SpawnRandom () override;
	std::vector<PlayerInfo> UpdateArray(std::vector<PlayerInfo> &info, World &world) override;
	void UpdateRegardingTo (PlayerInfo &info, Player * player, World & world) override;
	void RenderWith (DrawingEnviroment & drawEnv) override;
	void ProcessPlayerEvents (PlayerInfo &info, Player * player, sf::Event & e) override;
private:
	std::vector<Item*> m_items;
	int max_items = 1;
};

#endif

