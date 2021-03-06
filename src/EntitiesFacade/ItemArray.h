#ifndef ITEMARRAY_H
#define ITEMARRAY_H
#include "EntityArray.h"
#include <vector>
#include "PlayerInfo.h"
#include "../Entity/Item/Item.h"

class ItemArray : public EntityArray {
public:
	ItemArray(const sf::Vector2f &winsize);
	~ItemArray();
	void SpawnAt (const sf::Vector2f & pos, int switch_index) override;
	void SpawnRandom () override;
	size_t Size() const override { return m_items.size(); }
	std::vector<PlayerInfo> UpdateArray(std::vector<PlayerInfo> &info, World &world) override;
	void UpdateRegardingTo (PlayerInfo &info, Player * player, World & world) override;
	void RenderWith (DrawingEnviroment & drawEnv) override;
	void ProcessPlayerEvents (PlayerInfo &info, Player * player, sf::Event & e) override;
private:
	std::vector<Item*> m_items;
	const int max_size = 1;
};

#endif

