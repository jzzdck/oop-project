#ifndef ITEM_H
#define ITEM_H
#include "Entity.h"

/// @brief Mother class to all items in the game.
class Item : public Entity {
public:
	Item(sf::Vector2f pos, std::string keyword);
	
	/// @brief Set the current item's grab state.
	/// Items can be grabbed or not grabbed.
	void SetGrab(bool set) { is_grabbed = set; }
	
	/// @brief Check if the current item is already grabbed.
	/// @return The current grab state.
	bool IsGrabbed() const { return is_grabbed; }
	
	virtual void Draw(sf::RenderWindow & win) = 0;
	virtual ~Item() { }
private:
	bool is_grabbed;
};

#endif

