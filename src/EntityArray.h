#ifndef ENTITYARRAY_H
#define ENTITYARRAY_H
#include "Entity/Player.h"
#include "Graphics/DrawingEnviroment.h"
#include "Escena/Match/World.h"
#include "Entity/Entity.h"
#include "Game.h"
#include "PlayerInfo.h"
#include <iostream>
using namespace std;

class EntityArray {
public:
	EntityArray(const sf::Vector2f &winsize);
	virtual ~EntityArray() = default;
	
	int Update(Entity* entity, World &world);
	virtual void SpawnAt(const sf::Vector2f &pos, int switch_index) = 0;
	virtual void SpawnRandom() = 0;
	virtual std::vector<PlayerInfo> UpdateArray(std::vector<PlayerInfo> &info, World &world) = 0;
	virtual void UpdateRegardingTo(PlayerInfo &info, Player* player, World &world) = 0;
	virtual void ProcessPlayerEvents(PlayerInfo &info, Player* player, sf::Event &e) = 0;
	virtual void RenderWith(DrawingEnviroment &drawEnv) = 0;
protected:
	template<class T>
	std::vector<T*> EraseUnused(std::vector<T*> &v, World & world) {
		for (auto it = v.begin(); it != v.end();) {
			if (!(*it)->IsUsed() or world.IsUnbounded(*it)) {
				delete *it;
				it = v.erase(it);
			} else ++it;
		}
		
		return v;
	};
	
	sf::Vector2f m_winsize;
private:
};

#endif
