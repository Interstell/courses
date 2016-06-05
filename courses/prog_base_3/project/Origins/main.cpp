#include "player.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "food.hpp"

using namespace sf;

int main()
{
	srand(time(NULL));
	Game game;
	Gui gui;
	Player player(gui.view, 50, 50);
	Food food(gui, &player);
	while (gui.window.isOpen())
	{
		float GameTime = game.clock.getElapsedTime().asMicroseconds();
		GameTime /= (float)GAME_SPEED;
		game.clock.restart();
		Event event;
		while (gui.window.pollEvent(event)){
			if (event.type == Event::Closed)
				gui.window.close();
			/*if (event.type == Event::MouseWheelMoved){
				int sign = (event.mouseWheel.delta > 0) ? 1 : -1;
				gui.zoom(1 - sign*0.05);
			}*/
		}
		gui.proceedKeyboardInput(player, GameTime);
		gui.moveOnMouse(player, GameTime);
		player.update(gui.view, gui.scoreText, gui.massText);
		gui.window.clear();
		gui.drawBgAroundPlayer(player);
		food.draw(gui);
		gui.window.setView(gui.view);
		player.draw(gui.window);
		gui.window.draw(gui.scoreText);
		gui.window.draw(gui.massText);
		gui.window.display();
	}
	
	return 0;
}

