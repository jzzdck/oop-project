#include <ctime>
#include <cstdlib>
#include "Game.h"
using namespace std;

int main(int argc, char *argv[]) {
	
	srand(time(nullptr));
	
	Game LOVIGAME(1024, 840, "LOVIGAME");
	LOVIGAME.Run();
	
	return 0;
}

