#ifndef DYNAMICPLATFORMINFO_H
#define DYNAMICPLATFORMINFO_H

struct DynamicInfo {
	sf::Vector2f linear_speed = {0, 0}, ang_speed = {0, 0};
	sf::Vector2f start_pos = {-10000, -10000}, end_pos = {100000, 100000};
	float angle = 0, angle_vel = 0, radius = 0, starting_angle;
	
	void operator=(std::string s) {
		std::stringstream ss(s);
		ss >> start_pos.x >> start_pos.y 
		   >> end_pos.x >> end_pos.y
		   >> linear_speed.x >> linear_speed.y 
		   >> angle_vel >> radius >> angle;
	}
	
	std::string GetString(sf::Vector2f winsize, float scale) const {
		std::stringstream ss;
		ss << start_pos.x*scale/winsize.x << " " << start_pos.y*scale/winsize.y << " "
		   << end_pos.x*scale/winsize.x << " " << end_pos.y*scale/winsize.y << " "
		   << linear_speed.x << " " << linear_speed.y << " " 
		   << angle_vel << " " << radius*scale/winsize.y << " " << angle;
		
		return ss.str();
	} 
	
	void Reset() {
		DynamicInfo empty;
		*this = empty;
	}
};

#endif
