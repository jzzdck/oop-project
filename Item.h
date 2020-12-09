#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

/// @brief Mother class to all items in the game.
class Item : public Entity {
public:
	Item(std::string keyword);
	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow & win) = 0;
	virtual ~Item() { }
private:
};

#endif

