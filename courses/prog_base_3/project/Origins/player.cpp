#include "player.hpp"
#include "gui.hpp"
#include "game.hpp"

Player::Player(View& view, int X, int Y, int W, int H, Color bgColor){
	x = X;
	y = Y;
	Player::Player(view, W, H);
}


Player::Player(View& view, int W, int H, Color bgColor){
	this->view = &view;
	dx = 0; dy = 0; angle = 0;
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
	//TODO: texture
	//mainShape.setScale(0.5, 0.5);
	width = W;
	height = H;
	mainShape->setOrigin(width/2, height/2);
	//sprite.setTextureRect(IntRect(0, 0, mainRadius, mainRadius));
	mainShape->setPosition(x, y);
	shapes.push_back(new CellPart(mainShape, NULL));
}

Vector2i Player::getCoord(){
	return Vector2i(x, y);
}

void Player::move(double X, double Y, float time){
	x += X;
	y += Y;
	//cout << "R " << mainShape->getRadius() << " W " << width << " H " << height << endl;
	std::vector<CellPart*>::iterator it;
	for (it = shapes.begin(); it != shapes.end();){
		CellPart* child = *it;
		CellPart* parent = child->parent;
		if (parent == NULL) {
			++it;
			continue;
		}
		if (child->shape->getRadius() != 0) {
			Vector2f childPosition = Vector2f(view->getCenter().x
				+ parent->shape->getRadius()*splitVector.x*splitDistanceFactor,
				view->getCenter().y
				+ parent->shape->getRadius()*splitVector.y*splitDistanceFactor);
			child->shape->setPosition(childPosition);
		}
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

void Player::moveOnCoord(Vector2i coord){
	x = coord.x;
	y = coord.y;
}

void Player::draw(RenderWindow& window) {
	std::vector<CellPart*>::iterator it;
	for (it = shapes.begin(); it != shapes.end();){
		window.draw(*(*it)->shape);
		++it;
	}
}

void Player::setSpeed(double speed){
	this->speed = speed;
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
	mainShape->setRadius(width + (mass - START_MASS)*0.2);
	float sizeRatio = START_VIEW_SIZE.x / START_VIEW_SIZE.y;
	Vector2f newViewSize = Vector2f(START_VIEW_SIZE.x + (mass - START_MASS) * VIEW_SIZE_CHANGING_MULTIPLYER * sizeRatio, START_VIEW_SIZE.y + (mass - START_MASS)*VIEW_SIZE_CHANGING_MULTIPLYER);
	view.setSize(newViewSize);
	view.setCenter(x + width / 2, y + height / 2);
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

void Player::incMass(View* view){
	width++;
	height++;
	if (mass == score){
		score++;
	}
	mass++;
}

void Player::split() {
	if (splitAllowed) {
		splitAllowed = false;
		splitDirection = true;
		splitDistanceFactor = 1;
		splitVector = alignVectorNormal;
		splitSeconds = 0;

		std::vector<CellPart*> children;
		std::vector<CellPart*>::iterator it;
		for (it = shapes.begin(); it != shapes.end();){
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
			children.push_back(new CellPart(child,*it));
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
	width = sumRadius;
	height = sumRadius;
	mainShape->setRadius(sumRadius);
	for (it = shapes.begin(); it != shapes.end();){
		if ((*it)->shape != mainShape) {
			delete * it;
			it = shapes.erase(it);
		}
		else ++it;
	}

	/*newRadius = mainShape.getRadius() + childShape.getRadius();
	mainRadius = newRadius;
	mainRadius = newRadius;
	mainShape.setRadius(newRadius);
	childShape.setRadius(0);*/
}
