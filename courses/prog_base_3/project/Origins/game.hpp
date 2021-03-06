#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "GlobalHeader.hpp"

const int GAME_SPEED = 800;

class Game{
public:
	Clock clock;
	RenderWindow* window;
	Game();
	Game(RenderWindow* window);
	void run();
};

#endif