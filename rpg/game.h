#pragma once

#include "player.h"
#include "problem.h"
#include "list.h"
#include "save.h"

class game
{
private:
	player main_player;
	int people = 50;
	int court = 50;
	int tresury = 50;
	int game_state = 0;

	list<problem> list_problems;


public:
	game();
	game(player);
	void init();
	void start_game();
	void resume_game();
	void exit_game();
	void save_game();
	void effect(problem::option);

	// about problems
	problem gen_problem();
	void show_problem(problem);

	// load save
	save load_save();

	// getter and setter

	// player
	void s_player(player);
	player g_player();

	// game state
	void s_game_state(int);
	int g_game_state();

	// people
	void s_people(int);
	int g_people();

	// court
	void s_court(int);
	int g_court();

	// treasury
	void s_treasury(int);
	int g_treasury();

	// problem list
	void s_list_problems(list<problem>);
	list<problem> g_list_problems();
};

