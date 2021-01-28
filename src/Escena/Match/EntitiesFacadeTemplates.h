#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H

template<class T>
std::vector<T*> EraseUnused (std::vector<T*> &entities ) {
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
void UpdateOwnerships(int &currently_held, Player* player, std::vector<T*> &objects) {
	bool colliding_with_any_object = false;
	
	for (size_t i=0; i<objects.size(); ++i) { 
		if (objects.at(i)->CollidesWith(player->GetSprite()) && 
			objects.at(i)->Owner() == -1) 
		{
			if (currently_held != -1)
				objects.at(currently_held)->SetOwner(-1, player->GetSpeed());
			
			currently_held = i;
			objects.at(i)->SetOwner(player->GetIndex(), {0,0});
			colliding_with_any_object = true;
			break;
		}
	}
	
	if (not colliding_with_any_object) 
		for (size_t i=0; i<objects.size(); ++i)
			if (objects.at(i)->Owner() == player->GetIndex())
				currently_held = -1, objects.at(i)->SetOwner(-1, player->GetSpeed());
}

#endif
