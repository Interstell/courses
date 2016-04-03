#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

using namespace sf;

enum DIRECTION { RIGHT, LEFT, DOWN, UP };

class Player{
private:
	float x, y;
public:
	float w, h, dx, dy, speed;
	enum DIRECTION dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, float X, float Y, float W, float H);

	void update(float time);
	float getplayercoordinateX();
	float getplayercoordinateY();


};