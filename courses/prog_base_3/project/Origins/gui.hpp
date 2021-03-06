#ifndef  GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include "GlobalHeader.hpp"

class Player;

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 600;
const float INITIAL_ZOOM = 1.2;
const Vector2f START_VIEW_SIZE = Vector2f(WINDOW_WIDTH * INITIAL_ZOOM, WINDOW_HEIGHT * INITIAL_ZOOM);
const float VIEW_SIZE_CHANGING_MULTIPLYER = 6;
const int SCORE_TEXT_INITIAL_SIZE = 40;
const int MASS_TEXT_INITIAL_SIZE = 40;


class Gui{
public:
	RenderWindow* window;
	ContextSettings settings;
	int windowWidth, windowHeight;
	View view;
	Image bgImage;
	int bgImageSize;
	Texture bgTexture;
	Sprite bgSprite;
	Font font;
	Text scoreText;
	Text massText;
	Gui();
	Gui(RenderWindow* window);
	void drawBgAroundPlayer(Player& player);
	void proceedKeyboardInput(Player& player, float time);
	void moveOnMouse(Player& player, float time);
	void setView(int x, int y);
	static Color getRandomColor();
	static Vector2f getNormalVector(Vector2f vector);
	static Vector2f getVectorFromAngle(double angle);
	static Vector2f getShapeCenter(CircleShape shape);
	static Vector2f getDirectionVector(CircleShape shape1, CircleShape shape2);
	static double getDistanceBetwShapes(CircleShape shape1, CircleShape shape2);
	static double getAngleFromNormalVector(Vector2f vector);
	void zoom(float zoomFactor);
	FloatRect getCurrentViewCoord();
	FloatRect getCurrentRenderCoord();
	vector<CircleShape*> foodRenderQueue;
	void performFoodRenderQueue();
};

#endif