#include "player.hpp"

Player::Player(String F, float X, float Y, float W, float H){
	dx = 0; dy = 0; speed = 0; dir = (enum DIRECTION)0;
	File = F;
	w = W;
	h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X;
	y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Player::update(float time){
	switch (dir){
	case RIGHT:
		dx = speed;
		dy = 0;
		break;
	case LEFT:
		dx = -speed;
		dy = 0;
		break;
	case DOWN:
		dx = 0;
		dy = speed;
		break;
	case UP:
		dx = 0;
		dy = -speed;
		break;
	}
	x += dx*time;
	y += dy*time;
	speed = 0;
	sprite.setPosition(x, y);
}

float Player::getplayercoordinateX(){
	return x;
}
float Player::getplayercoordinateY(){
	return y;
}
