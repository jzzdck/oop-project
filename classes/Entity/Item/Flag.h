#ifndef FLAG_H
#define FLAG_H
#include "Item.h"

class Flag : public Item {
public:
	Flag(sf::Vector2f pos, bool who);
	void Draw(sf::RenderWindow & win) override;
private:
};

#endif

