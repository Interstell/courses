#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include "GlobalHeader.hpp"
#include "cellpart.hpp"

const double BOT_MIN_RADIUS = 50;
const double BOT_START_MASS = 0;
const double BOT_START_SPEED = 0.2;
const int BOT_ANGLE_STEP = 10;
static enum STATE{
	NEUTRAL = 1,
	AGRESSIVE,
	SCARED
};

class Bot {
public:
	Bot(double x, double y, double mass, double angle);
	CircleShape* mainShape;
	CellPart* mainCell;
	vector<CellPart*> shapes;
	Color color;
	Color outlineColor;
	Vector2f alignVector;
	Vector2f alignVectorNormal;
	enum STATE behaviour;
	void move(double X, double Y);
	void move(float time);
	void draw(RenderWindow& window);
	Vector2f getCoord();
	double mass;

	void split(); //todo split
	double splitDistanceFactor;
	bool splitAllowed = true;
	bool splitDirection; //true - forward, false - back
	Vector2f splitVector;
	float splitSeconds = 0;
	void splitUnion();
private:
	double x, y;
	double angle, speed;
};

#endif