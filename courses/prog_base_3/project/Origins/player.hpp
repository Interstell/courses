#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Player{
public:
	Vector2i getCoord();
	Player::Player(String Filename, View view, double X, double Y, double W, double H);
	Player::Player(String Filename, View view, double W, double H);
	Sprite sprite;
	void move(double X, double Y);
	void setSpeed(double Speed);
	double getSpeed();
	void update(View& view);
private:
	int x, y, dx, dy, width, height;
	double angleX, angleY, speed;
	String file;
	Image image;
	Texture texture;
	
};