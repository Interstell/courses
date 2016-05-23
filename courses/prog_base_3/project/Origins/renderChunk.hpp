#pragma once
#include <SFML/Graphics.hpp>
#include "foodParticle.hpp"
using namespace sf;

const int MAX_PARTICLES_PER_CHUNK = 15;

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
};