#define _CRT_SECURE_NO_WARNINGS
#include "player.hpp"
#include "game.hpp"
#include "gui.hpp"
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
	shape.setRadius(W);
	shape.setFillColor(color);
	shape.setOutlineThickness(-10);
	shape.setOutlineColor(outlineColor);
	//TODO: texture
	//shape.setScale(0.5, 0.5);
	width = W;
	height = H;
	shape.setOrigin(width/2, height/2);
	//sprite.setTextureRect(IntRect(0, 0, width, height));
	shape.setPosition(x, y);
}

Vector2i Player::getCoord(){
	return Vector2i(x, y);
}

void Player::move(double X, double Y, float time){
	x += X;
	y += Y;
	if (childShape.getRadius() != 0) {
		Vector2f childPosition = Vector2f(shape.getPosition().x 
			+ shape.getRadius()*splitVector.x*splitDistanceFactor, 
			shape.getPosition().y 
			+ shape.getRadius()*splitVector.y*splitDistanceFactor);
		childShape.setPosition(childPosition);
	}
	if (splitDirection) {
		splitDistanceFactor += time*SPLIT_DISTANCE_STEP;
	}
	else splitDistanceFactor -= time*SPLIT_DISTANCE_STEP / SPLIT_FORWARD_BACK_DIFFERENCE_FACTOR;
	if (splitDistanceFactor > SPLIT_MAX_FACTOR){
		splitDirection = false;
	}
	else if (splitDistanceFactor < 1.5) {
		splitDistanceFactor = 1.5;
	}
	
}

void Player::moveOnCoord(Vector2i coord){
	x = coord.x;
	y = coord.y;
}

void Player::draw(RenderWindow& window) {
	if (childShape.getRadius() != 0) {
		window.draw(childShape);
	}
	window.draw(shape);
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
	shape.setPosition(x, y);
	shape.setRadius(width + (mass - START_MASS)*0.2);
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
	

	
	/*FloatRect playerPos =  shape.getGlobalBounds();
	massText.setPosition(playerPos.left + (playerPos.width / 2)*0.95, playerPos.top + playerPos.height / 2);*/

	
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
	if (splitAllowed && shape.getRadius() > SPLIT_ALLOWED_RADIUS) {
		splitAllowed = false;
		splitDirection = true;
		splitDistanceFactor = 1;
		splitVector = alignVectorNormal;
		float newRadius = shape.getRadius() / 2;
		width /= 2;
		height /= 2;
		childShape = shape;
		shape.setRadius(newRadius);
		childShape.setRadius(newRadius);
		Vector2f mainPosition = shape.getPosition();
		Vector2f childPosition = Vector2f(shape.getPosition().x 
			+ newRadius*splitVector.x*splitDistanceFactor, 
			shape.getPosition().y 
			+ newRadius*splitVector.y*splitDistanceFactor);
		childShape.setPosition(childPosition);
	}
}
