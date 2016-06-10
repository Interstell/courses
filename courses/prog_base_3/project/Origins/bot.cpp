#include "bot.hpp"
#include "gui.hpp"

Bot::Bot(double x, double y, double mass, double angle) {
	this->x = x;
	this->y = y;
	this->mass = mass;
	this->angle = angle;
	speed = BOT_START_SPEED;
	color = Gui::getRandomColor();
	outlineColor = Color((color.r <= 30) ? 0 : color.r - 30, (color.g <= 30) ? 0 : color.g - 30, (color.b <= 30) ? 0 : color.b - 30);
	mainShape = new CircleShape;
	mainShape->setRadius(BOT_MIN_RADIUS + mass - BOT_START_MASS);
	mainShape->setFillColor(color);
	mainShape->setOutlineThickness(-10);
	mainShape->setOutlineColor(outlineColor);
	mainShape->setOrigin(mainShape->getRadius(), mainShape->getRadius());
	mainShape->setPosition(x, y);
	mainCell = new CellPart(mainShape, NULL);
	shapes.push_back(mainCell);
}

void Bot::move(double X, double Y, float time) {
	x += X;
	y += Y;
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
