#ifndef ENTITYARRAY_H
#define ENTITYARRAY_H
#include "Entity/Player.h"
#include "Graphics/DrawingEnviroment.h"
#include "Escena/Match/World.h"
#include "Entity/Entity.h"
#include "Game.h"
#include "PlayerInfo.h"
#include <iostream>
#include "Entity/Item/Item.h"
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
	sf::Vector2f m_winsize;
	bool PlayerPressedGrab(Controls &c, sf::Event & e, bool and_down);
	
	template<class T>
	std::vector<T*> EraseUnused(std::vector<T*> &v, World & world) {
		for (auto it = v.begin(); it != v.end();) {
			if (!(*it)->IsUsed() or world.IsUnbounded(*it)) {
				delete *it;
				*it = nullptr;
				it = v.erase(it);
			} else ++it;
		}
		
		return v;
	};
	
	template<class T>
	int FirstToCollide(const vector<T*> &v, Player* player, int &current) {
		//find the first item that collides and can be owned
		auto firt_collision = find_if(v.begin(), v.end(), [&](Item *item) {
			return player->CollidesWith(item) && item->Owner() == -1;
		});
		
		// find the item that belongs to the player, if it exists
		auto update_current = find_if(v.begin(), v.end(), [&](Item *item) {
			return player->CollidesWith(item) && item->Owner() == player->GetIndex();
		});
		
		if (update_current != v.end())
			current = update_current - v.begin();
		else
			current = -1;
		// because it may be updated in EraseUnused
		
		return firt_collision != v.end() ? firt_collision - v.begin() : -1;
	}
};

#endif
