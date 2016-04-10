#include "player.hpp"
#include "game.hpp"
Player::Player(String Filename, View view, double X, double Y, double W, double H){
	x = X;
	y = Y;
	Player::Player(Filename, view, W, H);
}


Player::Player(String Filename, View view, double W, double H){
	dx = 0; dy = 0; speed = 0; angleX = 0; angleY = 0;
	x = view.getCenter().x;
	y = view.getCenter().y;
	image.loadFromFile("images/" + Filename);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(0.5, 0.5); //@todo Dependence on size&score
	width = sprite.getScale().x * W;
	height = sprite.getScale().y * H;
	sprite.setOrigin(width / 2, height / 2);
	//sprite.setTextureRect(IntRect(0, 0, width, height));
	sprite.setPosition(x, y);
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
	sprite.setPosition(x, y);
	view.setCenter(x, y);
}