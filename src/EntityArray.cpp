#include "EntityArray.h"

EntityArray::EntityArray(const sf::Vector2f &winsize) :
	m_winsize(winsize)
{
	
}

int EntityArray::Update (Entity * entity, World &world) {
	sf::Vector2f response;
	
	entity->Update();
	entity->ApplyGravity(world.GetGravity());
	
	int collision = world.CollidesWith(entity, response), base_col = -1;
	if (collision == -1) entity->SetPlatform(nullptr);
	
	while (collision != -1) {
		if (collision == world.GetBaseIndex(0))
			base_col = 0;
		else if (collision == world.GetBaseIndex(1))
			base_col = 1;
		
		entity->ApplyResponse(-response);
		collision = world.CollidesWith(entity, response, collision+1);
	}
	
	return base_col;
}

