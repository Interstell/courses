#include "menu.hpp"
#include "game.hpp"

const Color ORANGE = Color(255, 85, 33);

typedef struct result_s{
	char name[50];
	char time[50];
	int score;
}* result_t;

void runMenu(RenderWindow* window) {
	Text newGame, highscores, exitBtn, credits;
	Sprite menuBgSprite, logoSprite, guideSprite;
	Texture menuBgTexture, logoTexture, guideTexture;

	Font fontMenu, fontGuide;
	fontMenu.loadFromFile("fonts/Brandon_med.otf");
	fontGuide.loadFromFile("fonts/Brandon_reg.otf");

	newGame.setString("NEW GAME");
	newGame.setFont(fontMenu);
	newGame.setColor(ORANGE);
	newGame.setPosition(100, 160);

	highscores.setString("HIGHSCORES");
	highscores.setFont(fontMenu);
	highscores.setColor(Color::Black);
	highscores.setPosition(100, 280);

	exitBtn.setString("EXIT");
	exitBtn.setFont(fontMenu);
	exitBtn.setColor(Color::Black);
	exitBtn.setPosition(100, 380);

	credits.setString("(c) Urukov Dmitry KP-52 KPI 2016");
	credits.setFont(fontGuide);
	credits.setColor(Color::Black);
	credits.setCharacterSize(15);
	credits.setPosition(930, 570);

	menuBgTexture.loadFromFile("images/menu_bg.png");
	menuBgSprite.setTexture(menuBgTexture);
	menuBgSprite.setPosition(0, 0);

	logoTexture.loadFromFile("images/logo.png");
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(700, 70);
	logoSprite.scale(0.9, 0.9);

	guideTexture.loadFromFile("images/guide.png");
	guideSprite.setTexture(guideTexture);
	guideSprite.setPosition(320, 400);


	window->setView(View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

	while (window->isOpen())
	{
		window->clear(Color::White);

		newGame.setCharacterSize(80);
		highscores.setCharacterSize(60);
		exitBtn.setCharacterSize(60);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		Vector2f mousePos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
		
		if (newGame.getGlobalBounds().contains(mousePos)){// intRect - прямокутна область
			newGame.setCharacterSize(90);
			if (Mouse::isButtonPressed(Mouse::Left)){
				Game game(window);
				game.run();
				window->setView(View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));
				continue;
			}
		}
		if (highscores.getGlobalBounds().contains(mousePos)){
			highscores.setCharacterSize(70);
			if (Mouse::isButtonPressed(Mouse::Left)){
				showHighscores(window);
				continue;
			}
		}
		if (exitBtn.getGlobalBounds().contains(mousePos)){
			exitBtn.setCharacterSize(70);
			if (Mouse::isButtonPressed(Mouse::Left))
				window->close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape) && Keyboard::isKeyPressed(Keyboard::LControl))
			window->close();
	
		window->draw(menuBgSprite);
		window->draw(logoSprite);
		window->draw(guideSprite);
		window->draw(newGame);
		window->draw(highscores);
		window->draw(exitBtn);

		if (logoSprite.getGlobalBounds().contains(mousePos)) {
			window->draw(credits);
		}
	
		window->display();
	}

}

int resultsCompare(const void* a, const void* b) {
	int dif = (*(result_t*)b)->score - (*(result_t*)a)->score;
	if (dif > 0) return 1;
	if (dif < 0) return -1;
	return 0;
}

void showHighscores(RenderWindow* window) {
	Font fontGuide, fontMenu;
	fontGuide.loadFromFile("fonts/Brandon_reg.otf");
	fontMenu.loadFromFile("fonts/Brandon_med.otf");

	Sprite menuBgSprite, logoSprite, scoreSprite;
	Texture menuBgTexture, logoTexture, scoreTexture;
	menuBgTexture.loadFromFile("images/menu_bg.png");
	menuBgSprite.setTexture(menuBgTexture);
	menuBgSprite.setPosition(0, 0);

	logoTexture.loadFromFile("images/logo.png");
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(700, 70);
	logoSprite.scale(0.9, 0.9);

	scoreTexture.loadFromFile("images/highscores_bg.png");
	scoreSprite.setTexture(scoreTexture);
	scoreSprite.setPosition(42, 55);

	Text highscores;
	highscores.setString("Highscores");
	highscores.setFont(fontMenu);
	highscores.setColor(ORANGE);
	highscores.setCharacterSize(60);
	highscores.setPosition(50, 50);

	FILE* input = fopen("highscores.json", "r");
	json_error_t error;
	json_t* root = json_loadf(input, 0, &error);
	fclose(input);
	int size = json_array_size(root);
	result_t * results = (result_t*)malloc(size * sizeof(struct result_s));
	for (int i = 0; i < size; i++) {
		json_t* res = json_array_get(root, i);
		json_t* name = json_object_get(res, "name");
		json_t* time = json_object_get(res, "time");
		json_t* score = json_object_get(res, "score");
		results[i] = (result_t)malloc(sizeof(struct result_s));
		strcpy(results[i]->name, json_string_value(name));
		strcpy(results[i]->time, json_string_value(time));
		results[i]->score = json_integer_value(score);
	}
	qsort(results, size, sizeof(result_t), resultsCompare);
	int limit = (size < 10) ? size : 10;
	vector<Text*> rows;
	for (int i = 0; i < limit; i++) {
		Text* row = new Text();
		char txt[300];
		sprintf(txt, "%2d. %s (%s) : %d", i + 1, results[i]->name, results[i]->time, results[i]->score);
		
		row->setString(String(txt));
		row->setFont(fontGuide);
		row->setColor(Color::Black);
		row->setCharacterSize(30);
		row->setPosition(50, 150 + 40 * i);
		rows.push_back(row);
	}

	window->setView(View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

	while (window->isOpen())
	{
		window->clear(Color::White);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		Vector2f mousePos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			break;

		window->draw(menuBgSprite);
		window->draw(logoSprite);
		window->draw(scoreSprite);
		window->draw(highscores);
		for (Text* txt : rows) {
			window->draw(*txt);
		}
		window->display();
	}
	
	for (int i = 0; i < size; i++) {
		free(results[i]);
	}
	free(results);
	for (Text* row : rows) {
		delete row;
	}

}
