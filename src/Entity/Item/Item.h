#ifndef ITEM_H
#define ITEM_H
#include "../Entity.h"

class Item : public Entity {
public:
	Item(sf::Vector2f pos, std::string keyword);
	void ApplyResponse(const sf::Vector2f &vec) override;
	
	void SetOwner(int owner) { m_owner = owner; }
	int Owner() const { return m_owner; }
	
	void Update() override;
	virtual void Draw(sf::RenderWindow & win);
	virtual ~Item() { }
private:
	int m_owner;
};

#endif

