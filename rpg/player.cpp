#include "pch.h"
#include "player.h"

// constructor
player::player()
{
	this->pname = "";
}

// setter for player_name
void player::s_pname(string value)
{
	this->pname = value;
}

// getter for player_name
string player::g_pname() {
	return this->pname;
}