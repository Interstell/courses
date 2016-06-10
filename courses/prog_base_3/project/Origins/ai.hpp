#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include "GlobalHeader.hpp"
#include "gui.hpp"
#include "bot.hpp"
class Player;

const double MATH_PI = 3.1415926535897932384;
const int MAX_BOTS_IN_RENDER = 5;
const double BIG_SMALL_DIFFERENCE_FACTOR = 0.1;
const int SIZE_DISPERSION_PERCENT = 40;

class AI {
public:
	AI(Gui* gui, Player* player, float* gameTime);
	Player* player;
	Gui* gui;
	vector<Bot*> bots;
	float* time;
	void initializeBots();
	void deleteInvisibleBots();
	void loadNewBots();
	void draw();

private:
};


#endif
