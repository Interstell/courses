#include "bot.hpp"
#include "gui.hpp"

Bot::Bot(double x, double y, double radius, double angle) {
	this->x = x;
	this->y = y;
	this->speed = BOT_START_SPEED;

	this->mass = radius - (BOT_MIN_RADIUS - BOT_START_MASS);
	this->angle = angle;
	speed = BOT_START_SPEED;
	color = Gui::getRandomColor();
	outlineColor = Color((color.r <= 30) ? 0 : color.r - 30, (color.g <= 30) ? 0 : color.g - 30, (color.b <= 30) ? 0 : color.b - 30);
	mainShape = new CircleShape;
	mainShape->setRadius(radius);
	mainShape->setFillColor(color);
	mainShape->setOutlineThickness(-10);
	mainShape->setOutlineColor(outlineColor);
	mainShape->setOrigin(mainShape->getRadius(), mainShape->getRadius());
	mainShape->setPosition(x, y);
	mainCell = new CellPart(mainShape, NULL);
	shapes.push_back(mainCell);
}

void Bot::move(double X, double Y) {
	x += X;
	y += Y;
	mainShape->setPosition(x, y);
}

void Bot::move(float time) {
	Vector2f vector = Gui::getVectorFromAngle(angle);	
	move(speed * time * vector.x, speed * time * vector.y);
	angle += pow(-1, rand() % 2)*((double)(rand() % BOT_ANGLE_STEP) / 100);
	if (angle > 2 * MATH_PI)
		angle -= 2 * MATH_PI;
}

void Bot::draw(RenderWindow& window) {
	std::vector<CellPart*>::iterator it;
	for (it = shapes.begin(); it != shapes.end();){
		window.draw(*(*it)->shape);
		++it;
	}
}

Vector2f Bot::getCoord() {
	return Vector2f(x, y);
}
