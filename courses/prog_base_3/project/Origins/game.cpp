#include "GlobalHeader.hpp"
#include "game.hpp"
#include "gui.hpp"
#include "player.hpp"
#include "food.hpp"
#include "ai.hpp"
#include "menu.hpp"

Game::Game(RenderWindow* window){
	this->window = window;
}

void Game::run() {
	float GameTime;
	Gui gui(window);
	Player player(gui.view, START_WIDTH_HEIGHT, START_WIDTH_HEIGHT, &gui);
	Food food(gui, &player);
	AI ai(&gui, &player);
	int exitPressed = 0;
	while (gui.window->isOpen())
	{
		GameTime = clock.getElapsedTime().asMicroseconds();
		GameTime /= (float)GAME_SPEED;
		clock.restart();
		Event event;
		
		while (gui.window->pollEvent(event)){
			if (event.type == Event::Closed) {
				gui.window->close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape) || player.gameOver) {
			if (!player.gameOver) gameOver(window, player.score);
			return;
		}
		gui.proceedKeyboardInput(player, GameTime);
		gui.moveOnMouse(player, GameTime);
		player.update(gui.view, gui.scoreText, gui.massText);
		gui.window->clear();
		gui.drawBgAroundPlayer(player);
		food.draw(gui);
		gui.performFoodRenderQueue();
		gui.window->setView(gui.view);
		ai.move(GameTime);
		ai.draw();
		player.draw(*(gui.window));
		gui.window->draw(gui.scoreText);
		gui.window->draw(gui.massText);
		gui.window->display();
	}
}
