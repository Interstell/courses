#include "food.hpp"

Food::Food(){
	foodArr.push_back(new FoodParticle(0, 0));
	foodArr.push_back(new FoodParticle(500, 500));
}

void Food::draw(Gui& gui){
	for (int i = 0; i < foodArr.size(); i++){
		foodArr[i]->draw(gui);
	}
}