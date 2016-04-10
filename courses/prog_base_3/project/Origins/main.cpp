#include "player.hpp"
#include "game.hpp"
#include "gui.hpp"


using namespace sf;

int main()
{
	Game game;
	Gui gui;

	Player player("cell1.png",gui.view, 300, 300);
	
	while (gui.window.isOpen())
	{
		float GameTime = game.clock.getElapsedTime().asMicroseconds();
		GameTime /= (float)game.GameSpeed;
		game.clock.restart();
		Event event;
		while (gui.window.pollEvent(event)){
			if (event.type == Event::Closed)
				gui.window.close();
		}
		gui.proceedWASDInput(player, GameTime);
		gui.moveOnMouse(player, GameTime);
		player.update(gui.view);
		gui.window.clear();
		gui.drawBgAroundPlayer(player);
		gui.window.draw(player.sprite);
		
		gui.window.setView(gui.view);
		gui.window.display();
	}
	
	return 0;
}

