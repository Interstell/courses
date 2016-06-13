#ifndef RENDERCHUNK_H_INCLUDED
#define RENDERCHUNK_H_INCLUDED

#include "GlobalHeader.hpp"
#include "foodParticle.hpp"
#include "player.hpp"

const int MAX_PARTICLES_PER_CHUNK = 10;

class FoodRenderChunk{
private:
	float leftX;
	float topY;
	int size;
	std::vector<FoodParticle*> foodVector;
	void fillWithParticles(void);
	Gui* gui;
public:
	FoodRenderChunk(Gui* gui, float leftX, float topY, float size);
	FoodRenderChunk(Gui* gui, FloatRect coord);
	FloatRect getCoord(void);
	void draw(void);
	void eatIntersectedFood(Player* player);
};

#endif
