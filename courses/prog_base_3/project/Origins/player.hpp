#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const int START_MASS = 10;
const double START_SPEED = 0.5;
const int SPLIT_ALLOWED_RADIUS = 60;
const float SPLIT_MAX_FACTOR = 10;
const float SPLIT_DISTANCE_STEP = 0.01;
const float SPLIT_FORWARD_BACK_DIFFERENCE_FACTOR = 3;

class Player{
public:
	Vector2i getCoord();
	Player::Player(View& view, int X, int Y, int W, int H, Color bgColor = Color(96, 121, 254));
	Player::Player(View& view, int W, int H, Color bgColor = Color(96, 121, 254));
	CircleShape shape;
	CircleShape childShape;
	Color color;
	Color outlineColor;
	void move(double X, double Y, float time);
	void moveOnCoord(Vector2i coord);
	void draw(RenderWindow& window);
	void setSpeed(double Speed);
	double getSpeed();
	void setAngle(double angle);
	double getAngle();
	Vector2f alignVectorNormal;
	View* view;
	void update(View& view, Text& scoreText, Text& massText);
	void incMass(View* view);
	float score;
	float mass;

	void split();
	double splitDistanceFactor;
	bool splitAllowed = true;
	bool splitDirection; //true - forward, false - back
	Vector2f splitVector;
	void splitUnion();
private:
	int x, y, dx, dy, width, height;
	double angle, speed;
	String file;
	Image image;
	Texture texture;
};