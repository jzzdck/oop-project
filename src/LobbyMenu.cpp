#include "LobbyMenu.h"

LobbyMenu::LobbyMenu(float width, float height) : 
	Menu(width, height, "lobby") 
{
	// LOBBY 
	// HOW MANY ROUNDS? < rounds_left >; 1 - inf
	// ROUNDS TYPE: RANDOM / MAX POINTS / TIMED / MAX POINTS AND TIMED
	// MAX POINTS: The first player to score X points wins the round.
	
	// TIMED: The player who scored more points when the clock stops wins the round.
	// Clock will stop at: X seconds.
	
	// MAX POINTS AND TIMED: A combination of the previous types,
	// The player who scores X points OR scores more points when the clock stops wins the round.
	// Clock will stop at: X seconds.
	
	// Random: Every round is different and decided at random. 
	// if timed HOW MUCH TIME
	// else if points HOW MANY POINTS TO WIN
	// else how much points and how much time
	
	// No matter the round type, the player who wins more rounds at the end wins the match.

	// START GAME
}

void LobbyMenu::Select (Game & g) {
	
}

void LobbyMenu::ProcessEvent (sf::Event & e, Game & g) {
	
}

void LobbyMenu::Update (Game & g) {
	
}

void LobbyMenu::Draw (sf::RenderWindow & win) {
	
}
