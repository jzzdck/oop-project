#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H

template<class T>
std::vector<T*> EraseUnused (std::vector<T*> entities ) {
	for (size_t i=0; i<entities.size(); ++i) {
		if (!entities[i]->IsUsed()) {
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	
	std::vector<T*> not_erased;
	for (size_t i=0; i<entities.size(); ++i)
		if (entities[i]) 
			not_erased.push_back(entities[i]);
	
	return not_erased;
}
	
template<class T> 
std::vector<T*> EraseUnbounded(std::vector<T*> &objects) {
	for (size_t i=0; i<objects.size(); ++i) {
		if (utils::IsUnbounded(objects[i]->GetSprite().getGlobalBounds(), {m_width, m_height})) {
			delete objects[i];
			objects[i] = nullptr;
		}
	}
	
	std::vector<T*> new_objects;
	for (size_t i=0; i<objects.size(); ++i)
		if (objects[i]) 
			new_objects.push_back(objects[i]);
	
	return new_objects;
}

template<class T> 
void UpdateOwnerships(Player* player, std::vector<T*> item_or_weapons) {
	bool colliding_with_any_object = false;
	
	for (T * item_or_weapon : item_or_weapons) { 
		if (item_or_weapon->CollidesWith(player->GetSprite()) && 
			item_or_weapon->Owner() == -1) 
		{
			player->AssignObject(item_or_weapon);
			colliding_with_any_object = true;
			break;
		}
	}
	
	if (not colliding_with_any_object) 
		for (T * item_or_weapon : item_or_weapons)
			if (item_or_weapon->Owner() == player->GetIndex())
				player->UnassignObject(item_or_weapon);
}

#endif
