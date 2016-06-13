#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "GlobalHeader.hpp"

#include "game.hpp"
#include "gui.hpp"
#include "food.hpp"
#include "ai.hpp"

void runMenu(RenderWindow* window);
void showHighscores(RenderWindow* window);
void gameOver(RenderWindow* window, int score);
void writeResult(string name, int score);
#endif