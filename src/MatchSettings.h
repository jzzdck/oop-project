#ifndef MATCHSETTINGS_H
#define MATCHSETTINGS_H
#include <string>

struct MatchSettings {
	int rounds_left = 5;
	int round_type = 0;
	int max_seconds = 60;
	int max_points = 7;
	std::string map_name = "MAIN";
	
	void Randomize() {
		round_type = rand()%4;
		max_points = rand()%(31-5) + 5;
		max_seconds = rand()%(201-15) + 15;
	}
};

#endif
