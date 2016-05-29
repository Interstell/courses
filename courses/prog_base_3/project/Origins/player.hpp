#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const int START_MASS = 10;

class Player{
public:
	Vector2i getCoord();
	Player::Player(View& view, int X, int Y, int W, int H, Color bgColor = Color(96, 121, 254));
	Player::Player(View& view, int W, int H, Color bgColor = Color(96, 121, 254));
	CircleShape shape;
	Color color;
	Color outlineColor;
	void move(double X, double Y);
	void moveOnCoord(Vector2i coord);
	void setSpeed(double Speed);
	double getSpeed();
	View* view;
	void update(View& view, Text& scoreText, Text& massText);
	void incMass(View* view);
	float score;
	float mass;
private:
	int x, y, dx, dy, width, height;
	double angleX, angleY, speed;
	String file;
	Image image;
	Texture texture;
};