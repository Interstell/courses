#include "gui.hpp"
#include "player.hpp"

//todo render queue for logical overlay

Gui::Gui(){
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(windowWidth, windowHeight), "Origins", sf::Style::Close, settings);
	window.setFramerateLimit(90);
	//window.setVerticalSyncEnabled(true);
	view.reset(FloatRect(150000, 150000, START_VIEW_SIZE.x, START_VIEW_SIZE.y));
	bgImageSize = 150;
	bgImage.loadFromFile("images/bg_white_large.png");
	bgTexture.loadFromImage(bgImage);
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	font.loadFromFile("scribble box demo.ttf");
	scoreText.setFont(font);
	massText.setFont(font);
	scoreText.setColor(Color(0,0,0));
	massText.setColor(Color(0,0,0));
	scoreText.setCharacterSize(SCORE_TEXT_INITIAL_SIZE);
	massText.setCharacterSize(MASS_TEXT_INITIAL_SIZE);
	scoreText.setOrigin(scoreText.getCharacterSize() / 2, scoreText.getCharacterSize() / 2);
	massText.setOrigin(massText.getCharacterSize()/2, massText.getCharacterSize()/2);
}

void Gui::drawBgAroundPlayer(Player& player){
	int numOfSquaresInViewX = view.getSize().x / bgImageSize + 15;
	int numOfSquaresInViewY = view.getSize().y / bgImageSize + 15;
	int currentSquareX = player.getCoord().x - player.getCoord().x % bgImageSize;
	int currentSquareY = player.getCoord().y - player.getCoord().y % bgImageSize;
	for (int i = currentSquareX - (numOfSquaresInViewX*bgImageSize) / 2; i <= currentSquareX + (numOfSquaresInViewX*bgImageSize) / 2; i += bgImageSize){
		for (int j = currentSquareY - (numOfSquaresInViewY*bgImageSize) / 2; j <= currentSquareY + (numOfSquaresInViewY*bgImageSize) / 2; j += bgImageSize){
			bgSprite.setPosition(i, j);
			window.draw(bgSprite);
		}
	}
}

void Gui::proceedKeyboardInput(Player& player, float time){
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.move(-player.getSpeed()*time, 0, time);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.move(player.getSpeed()*time, 0, time);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.move(0, -1.3*player.getSpeed()*time, time);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		player.move(0, 1.3*player.getSpeed()*time, time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Add)){
		zoom(0.99f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Subtract)){
		zoom(1.01f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		player.split();
	}
	
	if (Mouse::isButtonPressed(Mouse::Left)){
		std::cout << player.getCoord().x << " " << player.getCoord().y << " " << view.getCenter().x << " " << view.getCenter().y << std::endl;
	}
}

void Gui::setView(int x, int y){
	view.setCenter(x, y);
}

void Gui::moveOnMouse(Player& player, float time){
	//player.setSpeed(0.5f);
	//player.setSpeed(0);
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mousePos = window.mapPixelToCoords(pixelPos);
	Vector2f alignVector(mousePos.x - player.getCoord().x, mousePos.y - player.getCoord().y);
	double vectorLength = sqrt(pow(alignVector.x, 2) + pow(alignVector.y, 2));
	player.alignVectorNormal = Vector2f(alignVector.x / vectorLength, alignVector.y / vectorLength);
	if (player.mainCell->splitVector == Vector2f(0, 0)) {
		player.mainCell->splitVector = player.alignVectorNormal;
	}
	double angle = atan2(alignVector.y, alignVector.x);
	player.setAngle(angle);
	double curSpeed = player.getSpeed();
	if (vectorLength < player.mainShape->getRadius()) {
		curSpeed *= vectorLength / player.mainShape->getRadius();
	}
	
	player.move(curSpeed*time * alignVector.x / vectorLength, curSpeed * time * alignVector.y / vectorLength, time);
	player.update(view, scoreText, massText);
	//player.setSpeed(START_SPEED);
}

Color Gui::getRandomColor(){
	Color colorArray[] = {
		Color(244, 66, 54), //red
		Color(233, 29, 98), //pint
		Color(156, 38, 176), //purple
		Color(103, 57, 182), //deep purple
		Color(62, 80, 180), // indigo
		Color(32, 149, 242), //blue
		Color(2, 168, 244), //light blue
		Color(1, 187, 212),//cyan
		Color(1, 149, 135), //teal
		Color(75, 175, 79), //green
		Color(139, 194, 74), //lightGreen
		Color(204, 219, 56), //lime
		Color(255, 233, 59), //yellow
		Color(254, 193, 7), //amber
		Color(255, 151, 0), //orange
		Color(255, 85, 33), //deep orange
		Color(121, 85, 73), //brown
		Color(157, 157, 157), //grey
		Color(96, 124, 138), //blue grey
	};
	return colorArray[rand() % (sizeof(colorArray) / sizeof(Color))];
}

Vector2f Gui::getNormalVector(Vector2f vector) {
	double length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	return Vector2f(vector.x / length, vector.y / length);
}

Vector2f Gui::getVectorFromAngle(double angle) {
	return Vector2f(cos(angle), sin(angle));
}

Vector2f Gui::getShapeCenter(CircleShape shape) {
	return Vector2f(shape.getGlobalBounds().left + shape.getGlobalBounds().width/2,
		shape.getGlobalBounds().top + shape.getGlobalBounds().height/2);
}

Vector2f Gui::getDirectionVector(CircleShape shape1, CircleShape shape2) {
	Vector2f shape1Center = getShapeCenter(shape1);
	Vector2f shape2Center = getShapeCenter(shape2);
	return Vector2f(shape2Center.x - shape1Center.x, shape2Center.y - shape1Center.y);
}

double Gui::getDistanceBetwShapes(CircleShape shape1, CircleShape shape2) {
	Vector2f shape1Center = getShapeCenter(shape1);
	Vector2f shape2Center = getShapeCenter(shape2);
	return sqrt(pow(shape1Center.x - shape2Center.x, 2) + pow(shape1Center.y - shape2Center.y, 2));
}

double Gui::getAngleFromNormalVector(Vector2f vector) {
	double cosAngle = vector.x;
	double angle = acos(cosAngle);
	if (vector.y < 0) {
		angle += MATH_PI;
	}
	return angle;
}

void Gui::zoom(float zoomFactor){
	view.zoom(zoomFactor);
}

FloatRect Gui::getCurrentViewCoord(){
	Vector2f pixelPos = view.getCenter();
	Vector2f windowSize = view.getSize();
	pixelPos.x -= abs(windowSize.x / 2);
	pixelPos.y -= abs(windowSize.y / 2);
	//Vector2f worldPos = window.mapPixelToCoords(Vector2i(pixelPos.x, pixelPos.y));
	FloatRect curView = FloatRect(pixelPos.x, pixelPos.y, windowSize.x, windowSize.y);
	return curView;
}

FloatRect Gui::getCurrentRenderCoord(){
	FloatRect curView = getCurrentViewCoord();
	FloatRect renderView = FloatRect(curView.left - curView.width,
		curView.top - curView.height,
		curView.width * 3,
		curView.height * 3);
	/*FloatRect renderView = FloatRect(curView.left - curView.width/2,
		curView.top - curView.height/2,
		curView.width * 2,
		curView.height * 2);*/
	
	return renderView;
}