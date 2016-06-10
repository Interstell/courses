#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include "GlobalHeader.hpp"
#include "cellpart.hpp"

const double BOT_MIN_RADIUS = 50;
const double BOT_START_MASS = 10;
const double BOT_START_SPEED = 0.5;

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
	void move(double X, double Y, float time);
	void draw(RenderWindow& window);
	Vector2f getCoord();
	double mass;

	void split();
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
