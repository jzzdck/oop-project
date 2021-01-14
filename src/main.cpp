#include <ctime>
#include <cstdlib>
#include "Game.h"

// Toda la documentacion de Doxygen va en los .h, a excepcion del main, que tiene la mainpage.

int main(int argc, char *argv[]) {
	std::srand(time(nullptr));
	Game FROGGGAME(1248, 768, "FROGGGAME");
	FROGGGAME.Run();
	return 0;
}

/** 
	
	@mainpage Final Project for OOP: FROGGGAME

	@section intro_sec Introduction

	This is the documentation page for FROGGGAME. Here you'll find a brief summary of
	the main components that make the game.

	LOVIGAME is a 2D platform-fighting game where the goal is to steal
	each-other's flag.

	@subsection authors Authors:
	Gerónimo Rivoira - Lovino Tomás Francisco

**/

