#include "EntityArray.h"

EntityArray::EntityArray(const sf::Vector2f &winsize) :
	m_winsize(winsize)
{
	
}

int EntityArray::Update (Entity * entity, World &world) {
	sf::Vector2f response;
	int collision = world.CollidesWith(entity, response);
	int base_col = -1;

	if (collision == -1)
		entity->SetPlatform(nullptr);
	else while (collision != -1) {
		if (collision == world.GetBaseIndex(0))
			base_col = 0;
		else if (collision == world.GetBaseIndex(1))
			base_col = 1;
		
		entity->ApplyResponse(-response);
		collision = world.CollidesWith(entity, response, collision+1);
	}
	
	entity->Update();
	if (!entity->HasPlatform())
		entity->ApplyForce(world.GetGravity());
	
	return base_col;
}

bool EntityArray::PlayerPressedGrab (Controls &c, sf::Event & e, bool and_down) {
	bool down_key = c.KeyState("down");
	if (!and_down)
		down_key = !down_key;
	
	return e.type == sf::Event::KeyPressed && e.key.code == c.GetKey("grab") && down_key;
}

