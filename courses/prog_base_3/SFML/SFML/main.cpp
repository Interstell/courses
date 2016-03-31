#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

using namespace sf;

enum DIRECTION {RIGHT, LEFT, DOWN, UP};

class Player{
public:
	float x, y, w, h, dx, dy, speed;
	enum DIRECTION dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	
	Player(String F, float X, float Y, float W, float H){
		dx = 0; dy = 0; speed = 0; dir = (enum DIRECTION)0;
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	
	void update(float time){
		switch (dir){
		case RIGHT:
			dx = speed; 
			dy = 0;
			break;
		case LEFT:
			dx = -speed;
			dy = 0;
			break;
		case DOWN:
			dx = 0;
			dy = speed;
			break;
		case UP:
			dx = 0;
			dy = -speed;
			break;
		}
		x += dx*time;
		y += dy*time;
		speed = 0;
		sprite.setPosition(x, y);
	}
	
private:
};


int main()
{
	RenderWindow window(VideoMode(640, 480), "Learning SFML");
	
	float CurrentFrame = 0;
	Clock clock;
	
	Player p("hero.png", 250, 250, 96.0, 96.0);

	while (window.isOpen()){

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800; //speed

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) { 
			p.dir = LEFT;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >=3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) { 
			p.dir = RIGHT;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96 * 2, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) { 
			p.dir = UP;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96 * 3, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) { 
			p.dir = DOWN;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 0, 96, 96));
		}

		p.update(time);
		window.clear();
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}