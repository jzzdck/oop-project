#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H

template<class T>
bool IsBounded(T* entity, float out_factor = 0.5f) {
	auto pos = entity->GetSprite().getPosition();
	
	// get bools for cheking if entity is in between out_factor% + screen width/height 
	bool is_xout = pos.x > -win_width*0.5f && win_width*0.5f + win_width > pos.x;
	bool is_yout = pos.y > -win_height*0.5f && win_height*0.5f + win_height > pos.y;
	
	// if both conditions are met, then entity is bounded
	return is_yout && is_xout;
}

template<class T>
int UpdateEntity(T* entity) { 
	sf::Vector2f response;
	entity->Update();
	entity->ApplyGravity(m_world.GetGravity());
	
	int base_col = -1;
	int coll_index = m_world.CollidesWith(entity->GetSprite(), response);
	while (coll_index != -1) {
		if (coll_index == m_world.GetBaseIndex(0))
			base_col = 0;
		else if (coll_index == m_world.GetBaseIndex(1))
			base_col = 1;
		
		entity->ApplyResponse(response);
		coll_index = m_world.CollidesWith(entity->GetSprite(), response, coll_index+1);
	} 
	
	return base_col;
}
	
template<class T> 
void CheckBounds(std::vector<T*> &objects) {
	for (size_t i=0; i<objects.size(); ++i) {
		UpdateEntity(objects[i]);
		if (!IsBounded(objects[i])) {
			delete objects[i];
			objects[i] = nullptr;
		}
	}
	
	std::vector<T*> new_objects;
	for (size_t i=0; i<objects.size(); ++i)
		if (objects[i] != nullptr) 
			new_objects.push_back(objects[i]);
	
	objects = new_objects;
}

template<class T> 
void UpdateOwnerships(std::vector<T*> objects) {
	if (objects.empty()) return;
	
	for (Player *player : m_players) {
		bool update = true, pressed_grab = player->PressedGrab(objects[0]);
		
		for (T* object : objects) {
			if (object->Owner() == -1 && 
				object->CollidesWith(*player) && pressed_grab) 
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