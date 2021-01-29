#ifndef ENTITYARRAY_H
#define ENTITYARRAY_H
#include "Entity/Player.h"
#include "Graphics/DrawingEnviroment.h"
#include "Escena/Match/World.h"
#include "Entity/Entity.h"
#include "Game.h"
#include "PlayerInfo.h"

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
	void EraseUnused(std::vector<T*> &v, World & world) {
		for(size_t i=0;i<v.size();i++) { 
			if (!v.at(i)->IsUsed() or world.IsUnbounded(v.at(i))) {
				delete v.at(i);
				v.at(i) = nullptr;
			}
		}
		
		std::vector<T*> aux;
		for (size_t i=0;i<v.size();i++) { 
			if (v.at(i))
				aux.push_back(v.at(i));
		}
		
		v = aux;
	};
	
	sf::Vector2f m_winsize;
private:
};

#endif
