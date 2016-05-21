#include "foodParticle.hpp"

FoodParticle::FoodParticle(int x, int y){
	this->x = x;
	this->y = y;
	radius = FOOD_RADIUS;
	color = Gui::getRandomColor();
	shape.setRadius(radius);
	shape.setPointCount(FOOD_CIRCLE_POINTS);
	shape.setFillColor(color);
	shape.setPosition(x, y);
}

bool FoodParticle::getAliveStatus(void){
	return isAlive;
}

void FoodParticle::draw(Gui& gui){
	gui.window.draw(shape);
}

