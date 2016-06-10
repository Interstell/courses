#include "renderChunk.hpp"

FoodRenderChunk::FoodRenderChunk(Gui* gui, float leftX, float topY, float size){
	this->gui = gui;
	this->leftX = leftX;
	this->topY = topY;
	this->size = size;
	fillWithParticles();
}

FoodRenderChunk::FoodRenderChunk(Gui* gui, FloatRect coord){
	this->gui = gui;
	this->leftX = coord.left;
	this->topY = coord.top;
	this->size = coord.height;
	fillWithParticles();
}

FloatRect FoodRenderChunk::getCoord(void){
	return FloatRect(leftX, topY, size, size);
}

void FoodRenderChunk::fillWithParticles(void){
	while (foodVector.size() < MAX_PARTICLES_PER_CHUNK){
		int _x = (rand() % (int)size) + leftX;
		int _y = (rand() % (int)size) + topY;
		foodVector.push_back(new FoodParticle(_x, _y));
	}
}

void FoodRenderChunk::draw(void){
	for (FoodParticle* elem : foodVector){
		elem->draw(*gui);
	}
}

void FoodRenderChunk::eatIntersectedFood(Player* player){
	std::vector<FoodParticle*>::iterator itFood;
	std::vector<CellPart*>::iterator itShapes;
	for (itShapes = player->shapes.begin(); itShapes != player->shapes.end();) {
		for (itFood = foodVector.begin(); itFood != foodVector.end();) {
			double distanceBetwCenters = sqrt(
				pow((*itShapes)->shape->getPosition().x + (*itShapes)->shape->getRadius() - (*itFood)->getCoord().x, 2)
				+ pow((*itShapes)->shape->getPosition().y + (*itShapes)->shape->getRadius() - (*itFood)->getCoord().y, 2)
				);
			double sumRadius = (*itShapes)->shape->getRadius() + FOOD_RADIUS;
			if ((*itShapes)->shape->getGlobalBounds().contains((*itFood)->getCoord())
				&& sumRadius <= distanceBetwCenters){
				delete * itFood;
				itFood = foodVector.erase(itFood);
				player->incMass(player->view, *itShapes);
			}
			else ++itFood;
		}
		++itShapes;
	}


}