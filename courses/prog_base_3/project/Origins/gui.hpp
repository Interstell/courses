#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;
class Gui{
public:
	RenderWindow window;
	int windowWidth, windowHeight;
	View view;
	Image bgImage;
	int bgImageSize;
	Texture bgTexture;
	Sprite bgSprite;
	
	Gui();
	void drawBgAroundPlayer(Player player);
	void proceedWASDInput(Player& player, float time);
	void moveOnMouse(Player& player, float time);
	void setView(int x, int y);
private:

};