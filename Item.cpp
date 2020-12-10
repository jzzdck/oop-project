#include "Item.h"

Item::Item(sf::Vector2f pos, std::string keyword) 
	: Entity(pos, keyword), is_grabbed(false) {
	
}

