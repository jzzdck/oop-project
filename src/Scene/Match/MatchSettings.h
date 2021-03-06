#ifndef MATCHSETTINGS_H
#define MATCHSETTINGS_H
#include <string>
#include <vector>

struct MatchSettings {
	bool random_rounds = true;
	int rounds_left = 5;
	int round_type = 0;
	int max_seconds = 60;
	int max_points = 7;
	std::string map_name = "new_map";
	std::vector<int> rounds_won = { 0, 0 };
	
	void Randomize() {
		round_type = rand()%(4-1) + 1;
		max_points = rand()%(15-2) + 2;
		max_seconds = rand()%(150-15) + 15;
	}
};

#endif
