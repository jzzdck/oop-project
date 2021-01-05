#ifndef SHOVEL_H
#define SHOVEL_H
#include "Weapon.h"
#include <iostream>

class Shovel : public Weapon 
{
public:
	Shovel(sf::Vector2f pos);
	void Draw(sf::RenderWindow & win) override;
	void Action() override { std::cout << "CLANK" << std::endl; }
private:
};

#endif

