#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

/// @brief Mother class to all items in the game.
class Item : public Entity {
public:
	Item();
	void Update ( ) override;
	void Draw (sf::RenderWindow & win) override;
private:
};

#endif

