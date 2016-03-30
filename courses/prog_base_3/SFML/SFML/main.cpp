#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Learning SFML");

	Image heroimage;
	heroimage.loadFromFile("hero.png");

	Texture herotexture;
	herotexture.loadFromImage(heroimage);

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(50, 25);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) { herosprite.move(-0.1, 0); herosprite.setTextureRect(IntRect(0, 96, 96, 96)); }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { herosprite.move(0.1, 0); herosprite.setTextureRect(IntRect(0, 96 * 2, 96, 96)); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { herosprite.move(0, -0.1); herosprite.setTextureRect(IntRect(0, 96 * 3, 96, 96)); }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { herosprite.move(0, 0.1); herosprite.setTextureRect(IntRect(0, 0, 96, 96)); }

		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}