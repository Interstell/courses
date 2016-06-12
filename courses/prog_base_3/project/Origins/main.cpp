#include "GlobalHeader.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "food.hpp"
#include "ai.hpp"

int main()
{
	srand(time(NULL));
	float GameTime;
	Game game;
	Gui gui;
	Player player(gui.view, START_WIDTH_HEIGHT, START_WIDTH_HEIGHT);
	Food food(gui, &player);
	AI ai(&gui, &player);
	
	while (gui.window.isOpen())
	{
		GameTime = game.clock.getElapsedTime().asMicroseconds();
		GameTime /= (float)GAME_SPEED;
		game.clock.restart();
		Event event;
		while (gui.window.pollEvent(event)){
			if (event.type == Event::Closed) {
				gui.window.close();
			}
		}
		gui.proceedKeyboardInput(player, GameTime);
		gui.moveOnMouse(player, GameTime);
		player.update(gui.view, gui.scoreText, gui.massText);
		gui.window.clear();
		gui.drawBgAroundPlayer(player);
		food.draw(gui);
		gui.window.setView(gui.view);
		ai.move(GameTime);
		ai.draw();
		player.draw(gui.window);
		gui.window.draw(gui.scoreText);
		gui.window.draw(gui.massText);
		gui.window.display();
	}
	
	return 0;
}

