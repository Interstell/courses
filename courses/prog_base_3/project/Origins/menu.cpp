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
				showHighscores(window);
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
				//gameOver(window, 322);
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

void gameOver(RenderWindow* window, int score) {
	Font fontGuide, fontMenu;
	fontGuide.loadFromFile("fonts/Brandon_reg.otf");
	fontMenu.loadFromFile("fonts/Brandon_med.otf");

	Sprite menuBgSprite, logoSprite, labelSprite;
	Texture menuBgTexture, logoTexture, labelTexture;
	menuBgTexture.loadFromFile("images/menu_bg.png");
	menuBgSprite.setTexture(menuBgTexture);
	menuBgSprite.setPosition(0, 0);

	logoTexture.loadFromFile("images/logo.png");
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(700, 70);
	logoSprite.scale(0.9, 0.9);

	Text gameOver, userScore, userName, userDescr;

	gameOver.setString("GAME OVER");
	gameOver.setFont(fontMenu);
	gameOver.setColor(ORANGE);
	gameOver.setCharacterSize(60);
	gameOver.setPosition(100, 20);

	userScore.setString("Your score is: " + to_string(score));
	userScore.setFont(fontGuide);
	userScore.setColor(Color::Black);
	userScore.setCharacterSize(40);
	userScore.setPosition(100, 100);

	userDescr.setString("Type your name below and press Tab");
	userDescr.setFont(fontGuide);
	userDescr.setColor(Color::Black);
	userDescr.setCharacterSize(40);
	userDescr.setPosition(100, 150);

	userName.setString("");
	userName.setFont(fontGuide);
	userName.setColor(Color::Black);
	userName.setCharacterSize(50);
	userName.setPosition(100, 210);
	
	RectangleShape border;
	border.setSize(Vector2f(544, 65));
	border.setPosition(93, 216);
	border.setOutlineColor(ORANGE);
	border.setOutlineThickness(5);
	border.setFillColor(Color::Transparent);

	window->setView(View(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));
	string userInput="";

	while (window->isOpen())
	{
		window->clear(Color::White);

		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::TextEntered){
				if (isalnum(event.text.unicode) && userInput.length() < 20){
					userInput += event.text.unicode;
					userName.setString(userInput);
				}
			}
		}
		Vector2f mousePos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			break;
		if (Keyboard::isKeyPressed(Keyboard::BackSpace) && userInput.length() > 0) {
			userInput.erase(userInput.length() - 1);
			userName.setString(userInput);
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab) && userInput.length() > 0) {
			writeResult(userInput, score);
			return;
		}

		window->draw(menuBgSprite);
		window->draw(logoSprite);
		window->draw(gameOver);
		window->draw(userScore);
		window->draw(userDescr);
		window->draw(userName);
		window->draw(border);
		

		window->display();
	}
}

void writeResult(string name, int score) {
	FILE* file = fopen("highscores.json", "r");
	json_error_t error;
	json_t* root = json_loadf(file, 0, &error);
	fclose(file);
	time_t timeLocal = time(NULL);
	struct tm* time = localtime(&timeLocal);
	char timeStr[100];
	strftime(timeStr, sizeof(timeStr), "%d.%m.%Y %H:%M", time);
	json_t* res = json_pack("{s:s,s:s,s:i}", "name", name.c_str(), "time", timeStr, "score", score);
	json_array_append(root, res);
	file = fopen("highscores.json", "w");
	json_dumpf(root, file, JSON_INDENT(3));
	fclose(file);
}
