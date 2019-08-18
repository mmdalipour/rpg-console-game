#pragma once
#include "player.h"
#include "list.h"
#include "problem.h"

class save
{
private:
	player main_player;
	list<problem> list_problems;
	int people;
	int court;
	int treasury;
	int game_state;
public:
	save();

	void s_main_player(player);
	player g_main_player();

	void s_list_problems(list<problem>);
	list<problem> g_list_problems();

	void s_people(int);
	int g_people();

	void s_court(int);
	int g_court();

	void s_treasury(int);
	int g_treasury();

	void s_game_state(int);
	int g_game_state();
};

