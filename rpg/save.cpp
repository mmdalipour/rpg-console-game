#include "pch.h"
#include "save.h"


save::save()
{
}

void save::s_main_player(player value) {
	this->main_player = value;
}

player save::g_main_player() {
	return this->main_player;
}

void save::s_list_problems(list<problem> value) {
	this->list_problems = value;
}

list<problem> save::g_list_problems() {
	return this->list_problems;
}

void save::s_people(int value) {
	this->people = value;
}

int save::g_people() {
	return this->people;
}

void save::s_court(int value) {
	this->court = value;
}

int save::g_court() {
	return this->court;
}

void save::s_treasury(int value) {
	this->treasury = value;
}

int save::g_treasury() {
	return this->treasury;
}

void save::s_game_state(int value) {
	this->game_state = value;
}

int save::g_game_state() {
	return this->game_state;
}
