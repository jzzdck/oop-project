#include "ItemArray.h"
#include <algorithm>
#include "../Entity/Item/Flag.h"
#include "../Utils/generalUtils.h"

ItemArray::ItemArray(const sf::Vector2f &winsize) :
	EntityArray(winsize)
{
	size_t randitems = rand()%1;
	for (size_t i=0; i<randitems; ++i)
		SpawnRandom();
}

void ItemArray::SpawnAt (const sf::Vector2f & pos, int switch_index) {
	m_items.push_back(new Flag(pos, switch_index));
}

void ItemArray::SpawnRandom () {
	SpawnAt({m_winsize.x * utils::randf(), m_winsize.y * utils::randf() }, rand()%2);
}

void ItemArray::UpdateRegardingTo (PlayerInfo &info, Player * player, World & world) {
	for (Item* item : m_items) {
		if (item->Owner() == player->GetIndex()) {
			if (info.item_index == -1)
				item->SetOwner(-1, player->GetSpeed());
			
			item->SetPos(player->GetBounds(), player->GetFacing());
			break;
		}
	}
}

void ItemArray::RenderWith (DrawingEnviroment & drawEnv) {
	for (Item* item : m_items)
		item->Render(drawEnv), drawEnv.AddToLayer(item, 5);
}

void ItemArray::ProcessPlayerEvents (PlayerInfo &info, Player * player, sf::Event & e) {
	int collision = FirstToCollide(m_items, player, info.item_index);
	
	if (PlayerPressedGrab(player->GetControls(), e, true)) {
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

std::vector<PlayerInfo> ItemArray::UpdateArray (std::vector<PlayerInfo> &info, World &world ) {
	m_items = EraseUnused(m_items, world);
	for (size_t i=0;i<m_items.size();i++) {
		int base_col = Update(m_items.at(i), world);
		int capturer = m_items.at(i)->WasCaptured(base_col);
		if (capturer != -1) 
			info.at(capturer).round_points++;	
	}
	
	return info;
}

ItemArray::~ItemArray ( ) {
	for (size_t i=0; i<m_items.size(); ++i) 
		delete m_items.at(i);
}

