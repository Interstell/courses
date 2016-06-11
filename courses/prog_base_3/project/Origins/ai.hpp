#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include "GlobalHeader.hpp"
#include "gui.hpp"
#include "bot.hpp"
class Player;

const int MAX_BOTS_IN_RENDER = 5;
const double BIG_SMALL_DIFFERENCE_FACTOR = 0;
const int SIZE_DISPERSION_PERCENT = 50;

class AI {
public:
	AI(Gui* gui, Player* player);
	Player* player;
	Gui* gui;
	vector<Bot*> bots;
	void initializeBots();
	void deleteInvisibleBots();
	void loadNewBots();
	void move(float time);
	void draw();

private:
};


#endif
