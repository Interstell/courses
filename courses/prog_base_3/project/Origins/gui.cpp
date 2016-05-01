#include "gui.hpp"
#include <iostream>
using namespace std;
Gui::Gui(){
	windowWidth = 1200;
	windowHeight = 600;
	window.create(VideoMode(windowWidth, windowHeight), "Origins");
	window.setFramerateLimit(60);
	view.reset(FloatRect(0, 0, windowWidth, windowHeight));
	bgImageSize = 250;
	bgImage.loadFromFile("images/bg1.png");
	bgTexture.loadFromImage(bgImage);
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
}

void Gui::drawBgAroundPlayer(Player player){
	/*int leftX = view.getCenter().x - view.getSize().x / 2;
	int startX = (player.getCoord().x + leftX) % bgImageSize;
	int leftY = view.getCenter().y - view.getSize().y / 2;
	int startY = (player.getCoord().y + leftY) % bgImageSize;
	int endX = startX + view.getSize().x;
	int endY = startY + view.getSize().y;
	for (int i = startX; i <= endX; i += bgImageSize){
	for (int j = startY; j <= endY; j += bgImageSize){
	bgSprite.setPosition(i, j);
	window.draw(bgSprite);
	}
	}*/
	int numOfSquaresInViewX = view.getSize().x / bgImageSize + 3;
	int numOfSquaresInViewY = view.getSize().y / bgImageSize + 3;
	int currentSquareX = player.getCoord().x - player.getCoord().x % bgImageSize;
	int currentSquareY = player.getCoord().y - player.getCoord().y % bgImageSize;
	for (int i = currentSquareX - (numOfSquaresInViewX*bgImageSize) / 2; i <= currentSquareX + (numOfSquaresInViewX*bgImageSize) / 2; i += bgImageSize){
		for (int j = currentSquareY - (numOfSquaresInViewY*bgImageSize) / 2; j <= currentSquareY + (numOfSquaresInViewY*bgImageSize) / 2; j += bgImageSize){
			bgSprite.setPosition(i, j);
			window.draw(bgSprite);
		}
	}
}

void Gui::proceedWASDInput(Player& player, float time){
	player.setSpeed(0.1);
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.move(-player.getSpeed()*time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.move(player.getSpeed()*time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.move(0, -player.getSpeed()*time);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		player.move(0, player.getSpeed()*time);
	}
	if (Mouse::isButtonPressed(Mouse::Left)){
		std::cout << player.getCoord().x << " " << player.getCoord().y << " " << view.getCenter().x << " " << view.getCenter().y << std::endl;
	}
	player.setSpeed(0);
}

void Gui::setView(int x, int y){
	view.setCenter(x, y);
}

void Gui::moveOnMouse(Player& player, float time){
	//player.setSpeed(0.3);
	player.setSpeed(0);
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f mousePos = window.mapPixelToCoords(pixelPos);
	Vector2f alignVector(mousePos.x - player.getCoord().x, mousePos.y - player.getCoord().y);
	double vectorLength = sqrt(pow(alignVector.x, 2) + pow(alignVector.y, 2));
	//float rotation = atan2(alignVector.y, alignVector.x) * 180 / 3.1415;
	player.move(player.getSpeed()*time * alignVector.x / vectorLength, player.getSpeed() * time * alignVector.y / vectorLength);
	player.update(view);
}