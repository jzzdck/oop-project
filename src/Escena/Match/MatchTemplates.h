#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H

template<class T>
bool IsUnbounded(T *entity) {
	float out_factor = 0.5f;
	auto pos = entity->GetSprite().getPosition();
	
	// get bools for cheking if entity is in between out_factor% + screen width/height 
	bool is_xout = pos.x < -win_width*out_factor || win_width*out_factor + win_width < pos.x;
	bool is_yout = pos.y < -win_height*out_factor || win_height*out_factor + win_height < pos.y;
	
	// if both conditions are met, then entity is bounded
	return is_yout || is_xout;
}

template<class T>
int UpdateEntity(T* entity) { 
	sf::Vector2f response;
	
	entity->Update();
	entity->ApplyGravity(m_world.GetGravity());
	
	int collision = m_world.CollidesWith(entity, response), base_col = -1;
	while (collision != -1) {
		if (collision == m_world.GetBaseIndex(0))
			base_col = 0;
		else if (collision == m_world.GetBaseIndex(1))
			base_col = 1;
		
		entity->ApplyResponse(-response);
		collision = m_world.CollidesWith(entity, response, collision+1);
	}

	return base_col;
}
	
template<class T> 
std::vector<T*> EraseUnbounded(std::vector<T*> objects) {
	for (size_t i=0; i<objects.size(); ++i) {
		UpdateEntity(objects[i]);
		if (IsUnbounded(objects[i])) {
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
