#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "GlobalHeader.hpp"
#include "renderChunk.hpp"
#include "player.hpp"
#include "gui.hpp"


const int NUM_OF_PARTICLES_IN_VIEW = 300;
const int CHUNK_SIZE_PIXELS = 800;

class Food{
private:
	//std::vector<FoodParticle*> foodVector;
	std::vector<FoodRenderChunk*> chunks;
	FoodRenderChunk* currentChunk;
	Player* player;
	FloatRect foodRenderRect;
public:
	Food::Food(Gui& gui, Player* player);
	void draw(Gui& gui);
	void initializeParticles(Gui& gui);
	void deleteInvisibleChunks(Gui& gui);
	void loadNewChunks(Gui& gui);
};

#endif
