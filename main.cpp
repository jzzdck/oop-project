#include <ctime>
#include <cstdlib>
#include "Game.h"
using namespace std;

/*

 * los comentarios que empiecen y terminen con asteriscos son "importantes" *
 * tratar de poner todos los includes en los .h (mas prolijo y coherente) *
 * si se quiere tener aun mas organizacion, incluir primero las bibliotecas necesarias de c++,
   despues las de SFML, despues los headers propios *

*/

int main(int argc, char *argv[]) {
	
	srand(time(nullptr));
	
	Game LOVIGAME(1024,840, "LOVIGAME");
	LOVIGAME.Run();
	
	return 0;
}

