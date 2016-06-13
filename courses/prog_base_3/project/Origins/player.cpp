#include "player.hpp"
#include "gui.hpp"
#include "game.hpp"
#include "bot.hpp"

Player::Player(View& view, int W, int H, Color bgColor){
	this->view = &view;
	angle = 0;
	splitDistanceFactor = -1;
	speed = START_SPEED;
	mass = START_MASS;
	score = START_MASS;
	x = view.getCenter().x;
	y = view.getCenter().y;
	color = Gui::getRandomColor();
	outlineColor = Color((color.r <= 30) ? 0 : color.r - 30, (color.g <= 30) ? 0 : color.g - 30, (color.b <= 30) ? 0 : color.b - 30);
	mainShape = new CircleShape;
	mainShape->setRadius(W);
	mainShape->setFillColor(color);
	mainShape->setOutlineThickness(-10);
	mainShape->setOutlineColor(outlineColor);
	//todo texture ??? what for?
	//mainShape.setScale(0.5, 0.5);
	width = W;
	height = H;
	mainShape->setOrigin(width/2, height/2);
	//sprite.setTextureRect(IntRect(0, 0, mainRadius, mainRadius));
	mainShape->setPosition(x, y);
	mainCell = new CellPart(mainShape, NULL);
	shapes.push_back(mainCell);
}

Vector2i Player::getCoord(){
	return Vector2i(x, y);
}

void Player::move(double X, double Y, float time){
	//todo correct jump factor
	x += X;
	y += Y;
	//cout << "R " << mainShape->getRadius() << " W " << width << " H " << height << endl;
	std::vector<CellPart*>::iterator it;
	for (it = shapes.begin(); it != shapes.end();){
		(*it)->shape->setOrigin((*it)->shape->getRadius(), (*it)->shape->getRadius());
		//(*it)->shape->setPointCount(rand() % 10 + 10);
		CellPart* child = *it;
		CellPart* parent = child->parent;
		double currentSplitFactor = splitDistanceFactor;
		if (parent == NULL) {
			++it;
			continue;
		}
		Vector2f currentSplitVector = child->splitVector;
		if (!child->jumpable) {
			currentSplitFactor = 1; //todo constant (useless??)
		}

		Vector2f parentCenter = Vector2f(parent->shape->getPosition().x, parent->shape->getPosition().y);
		Vector2f childPosition = Vector2f(parentCenter.x
			+ 2 * parent->shape->getRadius()*currentSplitVector.x*currentSplitFactor,
			parentCenter.y
			+ 2 * parent->shape->getRadius()*currentSplitVector.y*currentSplitFactor);
		child->shape->setPosition(childPosition);

		++it;
	}
	if (splitDirection) {
		splitDistanceFactor += time*SPLIT_DISTANCE_STEP;
	}
	else{
		splitDistanceFactor -= time*SPLIT_DISTANCE_STEP / SPLIT_FORWARD_BACK_DIFFERENCE_FACTOR;
		splitSeconds += time*GAME_SPEED / 1000000;
	}
	if (splitDistanceFactor > SPLIT_MAX_FACTOR){
		splitDirection = false;
	}
	else if (splitDistanceFactor <= 1) { //waiting for union
		splitDistanceFactor = 1;
		splitAllowed = true;
		if (splitSeconds >= UNION_WAINING_TIME) {
			splitUnion();
			splitSeconds = 0;
			splitDirection = true;
		}
	}
}

void Player::draw(RenderWindow& window) {
	std::vector<CellPart*>::iterator it;
	sumRadius = 0;
	for (it = shapes.begin(); it != shapes.end();){
		sumRadius += (*it)->shape->getRadius();
		window.draw(*(*it)->shape);
		++it;
	}
	averageRadius = sumRadius / shapes.size();
}

void Player::setSpeed(double speed){
	this->speed = speed;
}

void Player::setWidthHeight(double width, double height) {
	this->width = (int)width;
	this->height = (int)height;
}

double Player::getSpeed(){
	return speed;
}

void Player::setAngle(double angle) {
	this->angle = angle;
}

double Player::getAngle() {
	return angle;
}

void Player::update(View& view, Text& scoreText, Text& massText){
	mainShape->setPosition(x, y);
	//mainShape->setRadius(width + (mass - START_MASS)*0.2);
	mainShape->setRadius(width);
	float sizeRatio = START_VIEW_SIZE.x / START_VIEW_SIZE.y;
	// todo normal koefs for logic scale changing (both shapes and view)
	Vector2f currentViewSize = Vector2f(START_VIEW_SIZE.x
		+ (width - START_WIDTH_HEIGHT)
		* VIEW_SIZE_CHANGING_MULTIPLYER
		* sizeRatio,
		START_VIEW_SIZE.y
		+ (width - START_WIDTH_HEIGHT)
		*VIEW_SIZE_CHANGING_MULTIPLYER);
	if (currentViewSize.x - view.getSize().x > ZOOM_EPSILON_FACTOR*currentViewSize.x) {
		view.zoom(ZOOM_IN_FACTOR_PER_FRAME);
	}
	else if (view.getSize().x - currentViewSize.x > ZOOM_EPSILON_FACTOR*currentViewSize.y) {
		view.zoom(ZOOM_OUT_FACTOR_PER_FRAME);
	}
	//view.setSize(currentViewSize);
	view.setCenter(x + width/2, y + height /2);
	char scoreChar[30];
	sprintf(scoreChar, "Score %3.0f", score);
	char massChar[30];
	sprintf(massChar, "Mass %3.0f", mass);
	scoreText.setString(String(scoreChar));
	massText.setString(String(massChar));
	
	FloatRect viewCoord = FloatRect(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2, view.getSize().x, view.getSize().y);
	scoreText.setCharacterSize(viewCoord.height * SCORE_TEXT_INITIAL_SIZE / START_VIEW_SIZE.y);
	massText.setCharacterSize(viewCoord.height * MASS_TEXT_INITIAL_SIZE / START_VIEW_SIZE.y);
	
	scoreText.setPosition(viewCoord.left + scoreText.getCharacterSize(), viewCoord.top + viewCoord.height - scoreText.getCharacterSize());
	massText.setPosition(scoreText.getPosition().x + scoreText.getGlobalBounds().width - massText.getGlobalBounds().width,
		scoreText.getPosition().y - massText.getCharacterSize());

}

void Player::incMass(CellPart* part){
	if (part->shape == mainShape) {
		width++;
		height++;
	}
	part->shape->setRadius(part->shape->getRadius() + 1);
	mass++;
	if (mass >= score){
		score = mass;
	}
}

void Player::incMass(CellPart* part, double foodRadius) {
	double foodMass = foodRadius - BOT_MIN_RADIUS + BOT_START_MASS;
	if (part->shape == mainShape) { 
		width += foodMass;
		height += foodMass;
	}
	part->shape->setRadius(part->shape->getRadius() + foodMass);
	mass += foodMass;
	if (mass >= score) {
		score = mass;
	}
}

void Player::decMass(CellPart* part) {
	double radius = part->shape->getRadius();
	mass -= mass*(part->shape->getRadius() / sumRadius);
}

void Player::split() {
	if (splitAllowed) {
		splitAllowed = false;
		splitDirection = true;
		splitDistanceFactor = 1;
		splitSeconds = 0;

		std::vector<CellPart*> children;
		std::vector<CellPart*>::iterator it;

		for (it = shapes.begin(); it != shapes.end();) {
			if ((*it)->shape->getRadius() > SPLIT_ALLOWED_RADIUS) {
				splitVector = alignVectorNormal;
				break;
			}
			++it;
		}
		for (it = shapes.begin(); it != shapes.end();) {
			(*it)->jumpable = false;
			++it;
		}
		for (it = shapes.begin(); it != shapes.end();){
			//cout << (*it)->shape->getRadius() << endl;
			if ((*it)->shape->getRadius() < SPLIT_ALLOWED_RADIUS) {
				++it;
				continue;
			}
			int newRadius = (*it)->shape->getRadius() / 2;
			(*it)->shape->setRadius(newRadius);
			if ((*it)->shape == mainShape) {
				width = newRadius;
				height = newRadius;
			}
			CircleShape* child = new CircleShape();
			*child = *((*it)->shape);
			child->setRadius(newRadius);
			Vector2f mainPosition = (*it)->shape->getPosition();
			Vector2f childPosition = Vector2f(mainPosition.x
				+ newRadius*splitVector.x*splitDistanceFactor,
				mainPosition.y
				+ newRadius*splitVector.y*splitDistanceFactor);
			child->setPosition(childPosition);
			CellPart* cellChild = new CellPart(child, *it, splitVector);
			(*it)->child = cellChild;
			children.push_back(cellChild);
			++it;
		}
		for (it = children.begin(); it != children.end();) {
			shapes.push_back(*it);
			++it;
		}
	}
	

}

void Player::splitUnion() {
	std::vector<CellPart*>::iterator it;
	int sumRadius = 0;
	for (it = shapes.begin(); it != shapes.end();){
		sumRadius += (*it)->shape->getRadius();
		++it;
	}
	setWidthHeight(sumRadius, sumRadius);
	mainShape->setRadius(sumRadius);
	for (it = shapes.begin(); it != shapes.end();){
		if ((*it)->shape != mainShape) {
			delete * it;
			it = shapes.erase(it);
		}
		else ++it;
	}
}
