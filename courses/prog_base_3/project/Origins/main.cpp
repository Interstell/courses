#include "player.hpp"
#include "game.hpp"
#include "gui.hpp"


using namespace sf;

int main()
{
	srand(time(NULL));
	Game game;
	Gui gui;
	
	Player player(gui.view, 60, 60);
	
	while (gui.window.isOpen())
	{
		float GameTime = game.clock.getElapsedTime().asMicroseconds();
		GameTime /= (float)game.GameSpeed;
		game.clock.restart();
		Event event;
		while (gui.window.pollEvent(event)){
			if (event.type == Event::Closed)
				gui.window.close();
			if (event.type == Event::MouseWheelMoved){
				int sign = (event.mouseWheel.delta > 0) ? 1 : -1;
				gui.zoom(1 - sign*0.05);
			}
		}
		gui.proceedWASDInput(player, GameTime);
		gui.moveOnMouse(player, GameTime);
		player.update(gui.view);
		gui.window.clear();
		gui.drawBgAroundPlayer(player);
		gui.window.draw(player.shape);
		
		gui.window.setView(gui.view);
		gui.window.display();
	}
	
	return 0;
}

