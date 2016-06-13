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

void FoodParticle::draw(Gui& gui){
	gui.window->draw(shape);
}

Vector2f FoodParticle::getCoord(){
	return Vector2f(x, y);
}

void FoodParticle::setCoord(float x, float y){
	this->x = x;
	this->y = y;
}