#ifndef ENTITYARRAY_H
#define ENTITYARRAY_H
#include "Entity/Player.h"
#include "Graphics/DrawingEnviroment.h"
#include "Escena/Match/World.h"
#include "Entity/Entity.h"
#include "Game.h"

class EntityArray {
public:
	EntityArray(const sf::Vector2f &winsize);
	virtual ~EntityArray() = default;
	
	int Update(Entity* entity, World &world);
	virtual void SpawnAt(const sf::Vector2f &pos, int switch_index) = 0;
	virtual void SpawnRandom(const sf::Vector2f &pos) = 0;
	virtual void UpdateRegardingTo(Player* player, World &world) = 0;
	virtual void ProcessPlayerEvents(Player* player, sf::Event &e, Game &g) = 0;
	virtual void RenderWith(DrawingEnviroment &drawEnv) = 0;
protected:
//	#include "Escena/Match/EntitiesFacadeTemplates.h"
	sf::Vector2f m_winsize;
private:
};

#endif
