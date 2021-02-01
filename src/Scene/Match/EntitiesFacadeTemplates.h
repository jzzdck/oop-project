#ifndef MATCHTEMPLATES_H
#define MATCHTEMPLATES_H

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
