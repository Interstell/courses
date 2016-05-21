#pragma once
#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include "foodParticle.hpp"


using namespace sf;

class Food{
private:
	std::vector<FoodParticle*> foodArr;

public:
	Food::Food();
	void draw(Gui& gui);
};