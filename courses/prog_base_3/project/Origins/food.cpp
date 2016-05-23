#include "food.hpp"

Food::Food(Gui& gui, Player* player){
	this->player = player;
	initializeParticles(gui);
}

void Food::draw(Gui& gui){
	for (FoodRenderChunk* elem : chunks){
		elem->draw();
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
	//int chunksXNum = (rightTop.x - leftTop.x) / CHUNK_SIZE_PIXELS;
	//int chunksYNum = (leftDown.y - leftTop.y) / CHUNK_SIZE_PIXELS;
	//Vector2f center = gui.view.getCenter();
	for (int i = leftTop.x; i < rightTop.x; i += CHUNK_SIZE_PIXELS){
		for (int j = leftTop.y; j < leftDown.y; j += CHUNK_SIZE_PIXELS){
			std::cout << i << " " << j << " " << std::endl;
			chunks.push_back(new FoodRenderChunk(&gui, i, j, CHUNK_SIZE_PIXELS));
		}
	}
	/*Vector2i center = Vector2i((leftTop.x + rightTop.x) / 2, (leftTop.y + leftDown.y) / 2);
	player->moveOnCoord(center);
	gui.view.setCenter(Vector2f(center.x, center.y));*/
}

void Food::replaceInvisibleParticles(Gui& gui){
	/*FloatRect newRect = gui.getCurrentRenderCoord();
	if (newRect != foodRenderRect){
		for (int i = 0; i < foodVector.size(); i++){
			if (!newRect.contains(foodVector[i]->getCoord())){
				FloatRect curView = gui.getCurrentViewCoord();
				FoodParticle* del = foodVector[i];
				foodVector.erase(foodVector.begin() + i);
				i--;
				delete del;
			}
		}
	}
	std::cout << foodVector.size() << std::endl;*/
}

void Food::pushParticleInRect(FloatRect rect){
	/*int _x = rand() % (int)rect.width - abs(rect.left);
	int _y = rand() % (int)rect.height - abs(rect.top);
	foodVector.push_back(new FoodParticle(_x, _y));*/
}

void Food::fillRenderViewWithNewParticles(Gui& gui){
	FloatRect prev = foodRenderRect;
	FloatRect next = gui.getCurrentRenderCoord();
	FloatRect nullVector = FloatRect(0, 0, 0, 0);
	FloatRect rect1 = nullVector;
	FloatRect rect2 = nullVector;
	/*if (next.left > prev.left && next.top > prev.top){
		rect1 = FloatRect(next.left, prev.top + prev.height, next.width, next.top + next.height - prev.top - prev.height);
		rect2 = FloatRect(prev.left + prev.width, next.top, next.left + next.width - (prev.left + prev.width), next.top + next.height - (prev.top + prev.height));
		while (foodVector.size() < NUM_OF_PARTICLES_IN_VIEW){
			pushParticleInRect(rect1);
			pushParticleInRect(rect2);
		}
	}*/
	/*if (next.top > prev.top){
		rect1 = FloatRect(prev.left, prev.top, prev.width, next.top - prev.top);
	}
	else if (next.top < prev.top){
		rect1 = FloatRect(next.left, next.top + next.width, next.width, prev.top + prev.height - next.top - next.height);
	}
	if (next.left > prev.left){
		rect2 = FloatRect(prev.left, prev.top, next.left - prev.left, prev.height);
	}
	else if (next.left < prev.left){
		rect2 = FloatRect(next.left + next.width, prev.top, prev.left + prev.width - next.left - next.width, prev.height);
	}
	while (foodVector.size() < NUM_OF_PARTICLES_IN_VIEW){
		if (rect1 != nullVector) pushParticleInRect(rect1);
		if (rect2 != nullVector) pushParticleInRect(rect2);
	}*/
}
