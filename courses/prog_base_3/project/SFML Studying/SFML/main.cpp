#include "player.hpp"
#include "map.h"
#include "view.h"

// *******ATTENTION PLEASE******
//	This code is a part of educational guide on SFML library. 
//	I decided to start from learning and passing it in order to know all the opportunities this library offer
//	in order to work quicker with my real project.
//	I named variables and methods as the guide's author did, so they code WILL seem unreadable
//	Obviously, my own project will not contain such awful sh*t without camelCase and pool of magic constants.
//	Thank's for reading.
// *******ATTENTION PLEASE******

int main()
{
	RenderWindow window(VideoMode(640, 480), "Learning SFML");
	view.reset(sf::FloatRect(0, 0, 640, 480));
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

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
		if (Keyboard::isKeyPressed(Keyboard::Left)) { 
			p.dir = LEFT;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >=3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96, 96, 96));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) { 
			p.dir = RIGHT;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96 * 2, 96, 96));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) { 
			p.dir = UP;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 96 * 3, 96, 96));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) { 
			p.dir = DOWN;
			p.speed = 0.1;
			CurrentFrame += time*0.005;
			if (CurrentFrame >= 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * (int)CurrentFrame, 0, 96, 96));
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}

		p.update(time);
		viewmap(time);
			
		window.clear(Color(128, 106, 89));
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); 
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		window.draw(p.sprite);
		window.setView(view);
		window.display();
	}

	return 0;
}