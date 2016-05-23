#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include "renderChunk.hpp"


const int NUM_OF_PARTICLES_IN_VIEW = 300;
const int CHUNK_SIZE_PIXELS = 800;

using namespace sf;

class Food{
private:
	//std::vector<FoodParticle*> foodVector;
	std::vector<FoodRenderChunk*> chunks;
	Player* player;
	FloatRect foodRenderRect;
	void pushParticleInRect(FloatRect rect);
public:
	Food::Food(Gui& gui, Player* player);
	void draw(Gui& gui);
	void initializeParticles(Gui& gui);
	void replaceInvisibleParticles(Gui& gui);
	void fillRenderViewWithNewParticles(Gui& gui);
};