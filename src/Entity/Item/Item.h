#ifndef ITEM_H
#define ITEM_H
#include "../Entity.h"

/// @brief Mother class to all items in the game.
class Item : public Entity {
public:
	Item(sf::Vector2f pos, std::string keyword);
	void ApplyResponse(const sf::Vector2f &vec) override;
	
	/// @brief Set the current item's grab state.
	/// Items can be grabbed or not grabbed.
	void SetOwner(int owner) { m_owner = owner; }
	
	/// @brief Check if the current item is already grabbed.
	/// @return The current grab state.
	int Owner() const { return m_owner; }
	
	void Update() override;
	virtual void Draw(sf::RenderWindow & win) = 0;
	virtual ~Item() { }
private:
	int m_owner;
};

#endif

