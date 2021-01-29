#include "ItemArray.h"
#include <algorithm>
#include "Utils/Controls.h"
#include "Entity/Item/Flag.h"

ItemArray::ItemArray(const sf::Vector2f &winsize) :
	EntityArray(winsize)
{
	size_t randitems = rand()%15 + 5;
	for (size_t i=0; i<randitems; ++i)
		SpawnRandom();
}

void ItemArray::SpawnAt (const sf::Vector2f & pos, int switch_index) {
	switch (switch_index) {
	case 0:
		m_items.push_back(new Flag(pos, rand()%2));
		break;
	};
}

void ItemArray::SpawnRandom () {
	int index = rand()%max_items;
	
	switch (index) {
	case 0:
		m_items.push_back(new Flag( {m_winsize.x * utils::randf(), m_winsize.y * utils::randf() }, rand()%2));
		break;
	};
}

void ItemArray::UpdateRegardingTo (PlayerInfo &info, Player * player, World & world) {
	for(size_t i=0;i<m_items.size();i++)
		if (m_items.at(i)->Owner() == player->GetIndex())
			m_items.at(i)->SetPos(player->GetSprite().getGlobalBounds(), player->GetFacing());
}

void ItemArray::RenderWith (DrawingEnviroment & drawEnv) {
	for (Item* item : m_items)
		item->Render(drawEnv), drawEnv.AddToLayer(item, 3);
}

void ItemArray::ProcessPlayerEvents (PlayerInfo &info, Player * player, sf::Event & e) {
	int collision = FirstItemColliding(player);
	
	if (PlayerPressedGrab(player, e)) {
		if (collision != -1) {
			if (info.item_index != -1)
				m_items.at(info.item_index)->SetOwner(-1, player->GetSpeed());
			
			info.item_index = collision;
			m_items.at(collision)->SetOwner(player->GetIndex(), {0, 0});
		} else if (info.item_index != -1) {
			m_items.at(info.item_index)->SetOwner(-1, player->GetSpeed());
			info.item_index = -1;
		}
	}
}

int ItemArray::FirstItemColliding (Player * player) {
	for(size_t i=0;i<m_items.size();i++)
		if (player->CollidesWith(m_items.at(i)) && m_items.at(i)->Owner() == -1)
			return i;
	
	return -1;
}

bool ItemArray::PlayerPressedGrab (Player * player, sf::Event & e) {
	Controls c = player->GetControls();
	return e.type == sf::Event::KeyPressed && e.key.code == c.GetKey("grab") && c.KeyState("down");
}

std::vector<PlayerInfo> ItemArray::UpdateArray (std::vector<PlayerInfo> &info, World &world ) {
	EraseUnused(m_items, world);
	for(size_t i=0;i<m_items.size();i++) { 
		int base_col = Update(m_items.at(i), world);
		int capturer = m_items.at(i)->WasCaptured(base_col);
		if (capturer != -1) 
			info.at(capturer).round_points++;	
	}
	
	return info;
}

