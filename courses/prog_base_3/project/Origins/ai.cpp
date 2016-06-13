#include "ai.hpp"
#include "player.hpp"
#include "menu.hpp"

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
					Vector2f playerCellCenter = Gui::getShapeCenter(*(*itPlayerShapes)->shape);
					Vector2f botCellCenter = Gui::getShapeCenter(*(*itBotShapes)->shape);
					if (playerCellRadius / botCellRadius > EATING_SIZE_DIFFERENCE_FACTOR      //player eats bot
						&& (*itPlayerShapes)->shape->getGlobalBounds().contains(botCellCenter)) { 
						player->incMass(*itPlayerShapes, botCellRadius); 
						(*itBotShapes)->shape->setRadius(0);
					}
					else if (botCellRadius / playerCellRadius > EATING_SIZE_DIFFERENCE_FACTOR //bot eats player
						&& (*itBotShapes)->shape->getGlobalBounds().contains(playerCellCenter)) { 
						player->decMass(*itPlayerShapes);
						(*itPlayerShapes)->shape->setRadius(0);
						if (player->mass <= START_MASS) {
							gameOver(player->gui->window, player->score);
							player->gameOver = true;
						}
						if (*itPlayerShapes == player->mainCell && player->shapes.size() > 1) {
							player->mainCell = player->mainCell->child;
							player->mainShape = player->mainCell->shape;
							player->setWidthHeight((int)(player->mainShape->getRadius()), (int)(player->mainShape->getRadius()));
							player->mainCell->parent = NULL;
							itPlayerShapes = player->shapes.erase(itPlayerShapes);
							goto deletedPlayer;
						}
					}
				}
				++itBotShapes;
			}
			++itBot;
		}
		++itPlayerShapes;
	deletedPlayer:
		int smth = 0;
	}
}

void AI::botsInteraction() { //shame for n^4, though n is const
	vector<Bot*>::iterator itBotI;
	vector<CellPart*>::iterator itBotShapeI;
	vector<Bot*>::iterator itBotJ;
	vector<CellPart*>::iterator itBotShapeJ;
	for (itBotI = bots.begin(); itBotI != prev(bots.end(), 1);) {
		for (itBotShapeI = (*itBotI)->shapes.begin(); itBotShapeI != (*itBotI)->shapes.end();) {
			for (itBotJ = next(itBotI, 1); itBotJ != bots.end();) {
				for (itBotShapeJ = (*itBotJ)->shapes.begin(); itBotShapeJ != (*itBotJ)->shapes.end();) {
					if ((*itBotShapeI)->shape->getGlobalBounds().intersects((*itBotShapeJ)->shape->getGlobalBounds())) {
						double iRadius = (*itBotShapeI)->shape->getRadius();
						double jRadius = (*itBotShapeJ)->shape->getRadius();
						Vector2f iCenter = Gui::getShapeCenter(*(*itBotShapeI)->shape);
						Vector2f jCenter = Gui::getShapeCenter(*(*itBotShapeI)->shape);
						if (iRadius / jRadius > EATING_SIZE_DIFFERENCE_FACTOR      
							&& (*itBotShapeI)->shape->getGlobalBounds().contains(jCenter)) {
							(*itBotShapeI)->shape->setRadius((*itBotShapeI)->shape->getRadius() + (*itBotShapeJ)->shape->getRadius() - BOT_MIN_RADIUS);
							itBotShapeJ = (*itBotJ)->shapes.erase(itBotShapeJ);
							goto itBotShapeJErased;
						}
						else if (jRadius / iRadius > EATING_SIZE_DIFFERENCE_FACTOR
							&& (*itBotShapeJ)->shape->getGlobalBounds().contains(iCenter)){
							(*itBotShapeJ)->shape->setRadius((*itBotShapeJ)->shape->getRadius() + (*itBotShapeI)->shape->getRadius() - BOT_MIN_RADIUS);
							itBotShapeI = (*itBotI)->shapes.erase(itBotShapeI);
							goto itBotShapeIErased;
						}
					}
					++itBotShapeJ;
					itBotShapeJErased:
					int smth = 0;
				}
				++itBotJ; 
			}
			++itBotShapeI;
			itBotShapeIErased:
			int smth2 = 0;
		}
		++itBotI;
	}
}

void AI::botsSetBehaviourWithPlayer() {
	vector<Bot*>::iterator itBot;
	double searchRadius = SEARCH_RADIUS_FACTOR * player->mainShape->getRadius(); //todo constant
	for (itBot = bots.begin(); itBot != bots.end();) {
		double distance = Gui::getDistanceBetwShapes(*((*itBot)->mainShape), *(player->mainShape));
		if (distance < searchRadius) {
			if (player->averageRadius / (*itBot)->averageRadius > EATING_SIZE_DIFFERENCE_FACTOR) {
				(*itBot)->behaviour = SCARED;
				Vector2f newVector = Gui::getDirectionVector(*(player->mainShape), *((*itBot)->mainShape));
				newVector = Gui::getNormalVector(newVector);
				(*itBot)->angle = Gui::getAngleFromNormalVector(newVector);
			}
			else if ((*itBot)->averageRadius / player->averageRadius  > EATING_SIZE_DIFFERENCE_FACTOR) {
				(*itBot)->behaviour = AGRESSIVE;
				Vector2f newVector = Gui::getDirectionVector(*((*itBot)->mainShape), *(player->mainShape));
				newVector = Gui::getNormalVector(newVector);
				(*itBot)->angle = Gui::getAngleFromNormalVector(newVector);
			}
			else (*itBot)->behaviour = NEUTRAL;
		}
		++itBot;
	}
}

void AI::draw() {
	vector<Bot*>::iterator it;
	deleteInvisibleBots();
	loadNewBots();
	botsInteraction();
	playerInteraction();
	botsSetBehaviourWithPlayer();
	for (it = bots.begin(); it != bots.end();) {
		(*it)->draw(*(gui->window)); //bug ??
		++it;
	}
}
