#pragma once
#include <SFML/Graphics.hpp>
#include "gui.hpp"

using namespace sf;

const int FOOD_RADIUS = 20;
const int FOOD_CIRCLE_POINTS = 6;

class FoodParticle{
public:
	FoodParticle::FoodParticle(int x, int y);
	bool getAliveStatus(void);
	void draw(Gui& gui);
private:
	int x, y;
	Vector2f moveVector;
	int radius;
	CircleShape shape;
	Color color;
	bool isAlive;
};