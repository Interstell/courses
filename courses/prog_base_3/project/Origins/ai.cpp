#include "ai.hpp"
#include "player.hpp"

AI::AI(Gui* gui, Player* player) {
	this->gui = gui;
	this->player = player;
	initializeBots();
}

void AI::initializeBots() {
	FloatRect render = gui->getCurrentRenderCoord();
	while (bots.size() < MAX_BOTS_IN_RENDER) {
		double _x = rand() % (int)render.width + render.left;
		double _y = rand() % (int)render.height + render.top;
		double _rad = (player->mass + START_WIDTH_HEIGHT - START_MASS) 
			* (1 + pow(-1, rand() % 2)
			*(rand() % SIZE_DISPERSION_PERCENT / 100));
		bots.push_back(new Bot(_x, _y, _rad, rand() % 628 / 100));
	}
}

void AI::deleteInvisibleBots() {
	FloatRect render = gui->getCurrentRenderCoord();
	vector<Bot*>::iterator it;
	for (it = bots.begin(); it != bots.end();) {
		if (!render.contains((*it)->getCoord())) {
			delete * it;
			it = bots.erase(it);
		}
		else ++it;
	}
}

void AI::loadNewBots() {
	FloatRect render = gui->getCurrentRenderCoord();
	FloatRect view = gui->getCurrentViewCoord();
	while (bots.size() != MAX_BOTS_IN_RENDER) {
		double _x, _y, _rad, _angle;
		int side = rand() % 4;
		switch (side) {
		case 0: //left vertical
			_x = render.left + 10;
			_y = render.top + rand() % (int)render.height;
			_angle = 0 + (double)(rand() % 25) / 100; //15 deg
			break;
		case 1: //right vertical
			_x = render.left + render.width - 10;
			_y = render.top + rand() % (int)render.height;
			_angle = MATH_PI + pow(-1, rand() % 2)*((double)(rand() % 25) / 100); //+-15 deg from 180
			break;
		case 2: //top horizontal
			_x = render.left + rand() % (int)render.width;
			_y = render.top + 10;
			_angle = 3 * MATH_PI / 2 + pow(-1, rand() % 2)*((double)(rand() % 25) / 100); //+-15 deg from 270
			break;
		case 3: //bottom horizontal
			_x = render.left + rand() % (int)render.width;
			_y = render.top + render.height - 10;
			_angle = MATH_PI / 2 + pow(-1, rand() % 2)*((double)(rand() % 25) / 100); //+-15 deg from 270
			break;
		}
		_rad = (player->mass + START_WIDTH_HEIGHT - START_MASS)
			* (1 + pow(-1, rand() % 2)
			*((double)(rand() % SIZE_DISPERSION_PERCENT) / 100) - BIG_SMALL_DIFFERENCE_FACTOR);
		cout << _rad << endl;
		if (_rad < BOT_MIN_RADIUS) { //todo constant
			_rad = BOT_MIN_RADIUS;
		}
		bots.push_back(new Bot(_x, _y, _rad, _angle));
	}

}

void AI::move(float time) {
	vector<Bot*>::iterator it;
	for (it = bots.begin(); it != bots.end();) {
		(*it)->move(time);
		++it;
	}
}

void AI::playerInteraction() {
	vector<Bot*>::iterator itBot;
	vector<CellPart*>::iterator itBotShapes;
	vector<CellPart*>::iterator itPlayerShapes;
	for (itPlayerShapes = player->shapes.begin(); itPlayerShapes != player->shapes.end();) {
		for (itBot = bots.begin(); itBot != bots.end();) {
			for (itBotShapes = (*itBot)->shapes.begin(); itBotShapes != (*itBot)->shapes.end();) {
				if ((*itBotShapes)->shape->getGlobalBounds().intersects((*itPlayerShapes)->shape->getGlobalBounds())) {
					double playerCellRadius = (*itPlayerShapes)->shape->getRadius();
					double botCellRadius = (*itBotShapes)->shape->getRadius();
					Vector2f playerCellCenter = Vector2f((*itPlayerShapes)->shape->getGlobalBounds().left
						+ (*itPlayerShapes)->shape->getGlobalBounds().width / 2,
						(*itPlayerShapes)->shape->getGlobalBounds().top
						+ (*itPlayerShapes)->shape->getGlobalBounds().height / 2);
					Vector2f botCellCenter = Vector2f((*itBotShapes)->shape->getGlobalBounds().left
						+ (*itBotShapes)->shape->getGlobalBounds().width / 2,
						(*itBotShapes)->shape->getGlobalBounds().top
						+ (*itBotShapes)->shape->getGlobalBounds().height / 2);
					if (playerCellRadius / botCellRadius > EATING_SIZE_DIFFERENCE_FACTOR      //player eats bot
						&& (*itPlayerShapes)->shape->getGlobalBounds().contains(botCellCenter)) {
						player->incMass(*itPlayerShapes, botCellRadius);
						(*itBotShapes)->shape->setRadius(0);
					}
					else if (botCellRadius / playerCellRadius > EATING_SIZE_DIFFERENCE_FACTOR //bot eats player
						&& (*itBotShapes)->shape->getGlobalBounds().contains(playerCellCenter)) {
						player->decMass(*itPlayerShapes);
						(*itPlayerShapes)->shape->setRadius(0);
						//todo check for gameover on player->mass == 0
						if (player->mass <= 0) {
							exit(EXIT_SUCCESS);
						}
					}
				}
				++itBotShapes;
			}
			++itBot;
		}
		++itPlayerShapes;
	}
}

void AI::draw() {
	vector<Bot*>::iterator it;
	deleteInvisibleBots();
	loadNewBots();
	playerInteraction();
	for (it = bots.begin(); it != bots.end();) {
		(*it)->draw(gui->window);
		++it;
	}
}
