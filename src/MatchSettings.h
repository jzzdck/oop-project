#ifndef MATCHSETTINGS_H
#define MATCHSETTINGS_H
#include <string>

struct MatchSettings {
	bool is_timed;
	sf::Time total_time;
	int max_points;
	int rounds_left;
	std::string map_name;
};

#endif
