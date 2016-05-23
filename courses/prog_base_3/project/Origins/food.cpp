#include "food.hpp"

Food::Food(Gui& gui, Player* player){
	this->player = player;
	initializeParticles(gui);
}

void Food::draw(Gui& gui){
	deleteInvisibleChunks(gui);
	loadNewChunks(gui);
	for (FoodRenderChunk* elem : chunks){
		elem->draw();
		if (elem->getCoord().contains(gui.view.getCenter())){
			currentChunk = elem;
		}
	}
}

void Food::initializeParticles(Gui& gui){
	foodRenderRect = gui.getCurrentRenderCoord();
	Vector2i leftTop = Vector2i(foodRenderRect.left, foodRenderRect.top);
	leftTop.x -= abs(leftTop.x) % CHUNK_SIZE_PIXELS;
	leftTop.y -= abs(leftTop.y) % CHUNK_SIZE_PIXELS;
	Vector2i leftDown = Vector2i(foodRenderRect.left, foodRenderRect.top + foodRenderRect.height);
	leftDown.x -= abs(leftDown.x) % CHUNK_SIZE_PIXELS;
	leftDown.y += (CHUNK_SIZE_PIXELS - abs(leftDown.y) % CHUNK_SIZE_PIXELS);
	Vector2i rightTop = Vector2i(foodRenderRect.left + foodRenderRect.width, foodRenderRect.top);
	rightTop.x += (CHUNK_SIZE_PIXELS - abs(rightTop.x) % CHUNK_SIZE_PIXELS);
	rightTop.y -= abs(rightTop.y) % CHUNK_SIZE_PIXELS;
	for (int i = leftTop.x; i < rightTop.x; i += CHUNK_SIZE_PIXELS){
		for (int j = leftTop.y; j < leftDown.y; j += CHUNK_SIZE_PIXELS){
			std::cout << i << " " << j << " " << std::endl;
			chunks.push_back(new FoodRenderChunk(&gui, i, j, CHUNK_SIZE_PIXELS));
		}
	}
}

void Food::deleteInvisibleChunks(Gui& gui){
	std::vector<FoodRenderChunk*>::iterator it;
	for (it = chunks.begin(); it != chunks.end();){
		if (!gui.getCurrentRenderCoord().intersects((*it)->getCoord())){
			delete * it;
			it = chunks.erase(it);
		}
		else ++it;
	}
}

void Food::loadNewChunks(Gui& gui){
	foodRenderRect = gui.getCurrentRenderCoord();
	Vector2i leftTop = Vector2i(foodRenderRect.left, foodRenderRect.top);
	leftTop.x -= abs(leftTop.x) % CHUNK_SIZE_PIXELS;
	leftTop.y -= abs(leftTop.y) % CHUNK_SIZE_PIXELS;
	Vector2i leftDown = Vector2i(foodRenderRect.left, foodRenderRect.top + foodRenderRect.height);
	leftDown.x -= abs(leftDown.x) % CHUNK_SIZE_PIXELS;
	leftDown.y += (CHUNK_SIZE_PIXELS - abs(leftDown.y) % CHUNK_SIZE_PIXELS);
	Vector2i rightTop = Vector2i(foodRenderRect.left + foodRenderRect.width, foodRenderRect.top);
	rightTop.x += (CHUNK_SIZE_PIXELS - abs(rightTop.x) % CHUNK_SIZE_PIXELS);
	rightTop.y -= abs(rightTop.y) % CHUNK_SIZE_PIXELS;
	for (int i = leftTop.x; i < rightTop.x; i += CHUNK_SIZE_PIXELS){
		for (int j = leftTop.y; j < leftDown.y; j += CHUNK_SIZE_PIXELS){
			FloatRect curChunk = FloatRect(i, j, CHUNK_SIZE_PIXELS, CHUNK_SIZE_PIXELS);
			std::vector<FoodRenderChunk*>::iterator it;
			bool exist = false;
			for (it = chunks.begin(); it != chunks.end();){
				if ((*it)->getCoord() == curChunk){
					exist = true;
					break;
				}
				else ++it;
			}
			if (!exist){
				chunks.push_back(new FoodRenderChunk(&gui, i, j, CHUNK_SIZE_PIXELS));
			}
		}
	}
}
