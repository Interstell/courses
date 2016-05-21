#include "player.hpp"
#include "game.hpp"
#include "gui.hpp"
Player::Player(View view, int X, int Y, int W, int H, Color bgColor){
	x = X;
	y = Y;
	Player::Player(view, W, H);
}


Player::Player(View view, int W, int H, Color bgColor){
	dx = 0; dy = 0; speed = 0; angleX = 0; angleY = 0;
	x = view.getCenter().x;
	y = view.getCenter().y;
	color = Gui::getRandomColor();
	outlineColor = Color((color.r <= 30) ? 0 : color.r - 30, (color.g <= 30) ? 0 : color.g - 30, (color.b <= 30) ? 0 : color.b - 30);
	shape.setRadius(W);
	shape.setFillColor(color);
	shape.setOutlineThickness(-10);
	shape.setOutlineColor(outlineColor);
	//TODO: texture
	//shape.setScale(0.5, 0.5); //TODO: Dependence on size&score
	width = shape.getScale().x * W;
	height = shape.getScale().y * H;
	shape.setOrigin(width/2, height/2);
	//sprite.setTextureRect(IntRect(0, 0, width, height));
	shape.setPosition(x, y);
}

Vector2i Player::getCoord(){
	return Vector2i(x, y);
}

void Player::move(double X, double Y){
	x += X;
	y += Y;
}

void Player::setSpeed(double speed){
	this->speed = speed;
}

double Player::getSpeed(){
	return speed;
}

void Player::update(View& view){
	shape.setPosition(x - width/2, y - height/2);
	view.setCenter(x, y); //TODO: bgImageSize!!!
}