#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H
	
template<class T> 
std::vector<T*> EraseUnbounded(std::vector<T*> objects) {
	for (size_t i=0; i<objects.size(); ++i) {
		UpdateEntity(objects[i]);
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
void UpdateOwnerships(std::vector<T*> objects) {
	if (objects.empty()) return;
	
	for (Player *player : m_players) {
		bool update = true, pressed_grab = player->PressedGrab(objects[0]);
		
		for (T* object : objects) {
			if (object->Owner() == -1 && pressed_grab &&
				object->CollidesWith(player->GetSprite())) 
			{
				player->AssignObject(object);
				update = false;
				break;
			}
		}
		
		if (update) for (T* object : objects) {
			if (object->Owner() == player->GetIndex() && pressed_grab)
				player->UnassignObject(object);
		}
	}
}

#endif
