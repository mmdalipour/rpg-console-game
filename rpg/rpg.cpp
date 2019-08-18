// rpg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "game.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	// seed for rand() function
	srand(time(0));

	// create instance of game
	game my_game = game();

	my_game.init();

}
