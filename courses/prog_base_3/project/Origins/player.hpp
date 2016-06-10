#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GlobalHeader.hpp"
#include "cellpart.hpp"

const int START_MASS = 10;
const float START_WIDTH_HEIGHT = 50;
const double START_SPEED = 0.5;
const int SPLIT_ALLOWED_RADIUS = 70;
const float SPLIT_MAX_FACTOR = 4;
const float SPLIT_DISTANCE_STEP = 0.005;
const float SPLIT_FORWARD_BACK_DIFFERENCE_FACTOR = 10;
const float UNION_WAINING_TIME = 15; //seconds

class Player{
public:
	Vector2i getCoord();
	Player::Player(View& view, int W, int H, Color bgColor = Color(96, 121, 254));
	CircleShape* mainShape;
	CellPart* mainCell;
	//float mainRadius;
	std::vector<CellPart*> shapes;
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
	void incMass(View* view, CellPart* part);
	float score;
	float mass;

	void split();
	double splitDistanceFactor;
	bool splitAllowed = true;
	bool splitDirection; //true - forward, false - back
	Vector2f splitVector;
	float splitSeconds = 0;
	void splitUnion();
private:
	int x, y, dx, dy, width, height;
	double angle, speed;
	String file;
	Image image;
	Texture texture;
};

#endif