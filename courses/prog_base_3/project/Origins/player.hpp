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
const float ZOOM_IN_FACTOR_PER_FRAME = 1.0005f;
const float ZOOM_OUT_FACTOR_PER_FRAME = 0.9995f;
const float ZOOM_EPSILON_FACTOR = 0.002;
const float ZOOM_OFF_RADIUS = 250;
const double SPEED_DECREASE_BY_1_RADIUS = 0.005;
const double MIN_SPEED = 0.2;
class Gui;

class Player{
public:
	Vector2i getCoord();
	Player::Player(View& view, int W, int H, Gui* gui);
	CircleShape* mainShape;
	CellPart* mainCell;
	//float mainRadius;
	std::vector<CellPart*> shapes;
	Gui* gui;
	Color color;
	Color outlineColor;
	void move(double X, double Y, float time);
	void draw(RenderWindow& window);
	void setSpeed(double Speed);
	void setXY(int x, int y);
	void setWidthHeight(double width, double height);
	double getSpeed();
	void setAngle(double angle);
	double getAngle();
	Vector2f alignVectorNormal;
	View* view;
	Vector2f currentViewSize;
	void update(View& view, Text& scoreText, Text& massText);
	void incMass(CellPart* part);
	void incMass(CellPart* part, double foodRadius);
	void decMass(CellPart* part);
	float score;
	float mass;
	double sumRadius;
	double averageRadius;
	void split();
	double splitDistanceFactor;
	bool splitAllowed = true;
	bool splitDirection; //true - forward, false - back
	Vector2f splitVector;
	float splitSeconds = 0;
	void splitUnion();
	bool gameOver = false;
private:
	int x, y, dx, dy, width, height;
	double angle, speed;
};

#endif