#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class BotCell{
private:
	int x, y, dx, dy, width, height;
	double speed;
	String file;
	Image image;
	Texture texture;
};