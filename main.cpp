#include <ctime>
#include <cstdlib>
#include "Game.h"
#define LOVIGAME RIVOGAME
using namespace std;

int main(int argc, char *argv[]) {
	srand(time(nullptr));
	Game LOVIGAME(1248, 768, "GABOGAME");
	RIVOGAME.Run();
	return 0;
}

