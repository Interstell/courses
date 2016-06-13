#include "GlobalHeader.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "food.hpp"
#include "ai.hpp"
#include "menu.hpp"

int main()
{
	srand(time(NULL));
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window;
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Origins", sf::Style::Close, settings);
	window.setFramerateLimit(90);
	
	runMenu(&window);	
	
	return 0;
}

