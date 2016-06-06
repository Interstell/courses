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
	std::vector<FoodParticle*>::iterator it;
	bool exist = false;
	for (it = foodVector.begin(); it != foodVector.end();){
		if (player->mainShape->getGlobalBounds().contains((*it)->getCoord())){
			//@todo check by radius
			delete * it;
			it = foodVector.erase(it);
			player->incMass(player->view);
		}
		/*else if (player->childShape.getRadius() != 0 && player->childShape.getGlobalBounds().contains((*it)->getCoord())) {
			delete * it;
			it = foodVector.erase(it);
			player->incMass(player->view);
		}*/
		else ++it;
	}
}