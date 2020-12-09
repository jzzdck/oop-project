#ifndef FLAG_H
#define FLAG_H
#include "Item.h"

class Flag : public Item {
public:
	Flag(float intial_x, float initial_y, bool who);
	void Draw(sf::RenderWindow & win) override;
private:
};

#endif

