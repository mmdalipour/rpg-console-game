#include "pch.h"
#include "game.h"
#include "storage.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// constructor #1
game::game() {

}

// contructor #2
game::game(player main_player)
{
	this->main_player = main_player;
}

// start a new instance of game
void game::init() {
	string pname = "";

	// welcome
	cout << "Welcome to the RPGConsole game\n";

	// create a new player instance
	player my_player = player();

	if (!check_save())
	{
		// let user choose it's name
		cout << "Choose your name: ";

		// read user input
		cin >> pname;

		// set player name
		my_player.s_pname(pname);
	}
	else
	{
		save my_save = load_save();

		// set player name
		my_player.s_pname(my_save.g_main_player().g_pname());
	}

	this->main_player = my_player;

	// welcome user
	cout << "Welcome " << my_player.g_pname() << endl;

	bool wrong_select = false;

	do
	{
		// menu selected index
		int menu_select = 0;

		// menu options
		cout << "What do you want to do next?" << endl;
		cout << "[1] Start a new game" << endl;
		cout << "[2] Resume game" << endl;
		cout << "[3] Exit game" << endl;

		// read user input
		cin >> menu_select;

		switch (menu_select)
		{
		case 1:
			// create a new game
			//cout << "you have started a new game" << endl;
			start_game();
			wrong_select = false;
			break;
		case 2:
			// check if has saved game if so resume game from last point if not cout "you have no saved game"
			//cout << "you have started your last game" << endl;
			if (check_save()) {
				//cout << "you have started your last game" << endl;
				resume_game();
				wrong_select = false;
			}
			else {
				cout << "you don't have any saved games" << endl;
				wrong_select = true;
			}
			break;
		case 3:
			// exit game and close cmd no need to save game state because we are not starting it yet!
			//cout << "you have selected to exit the game" << endl;
			exit_game();
			wrong_select = true;
			break;
		default:
			// wrong option selected show the menu untill the right answer given
			cout << "wrong option please select one of the following options in the menu" << endl;
			wrong_select = true;
			break;
		}
	} while (wrong_select);
}

// start a new game
void game::start_game() {
	// set all values to their default values
	this->people = 50;
	this->court = 50;
	this->tresury = 50;

	this->game_state = 0;

	// store problems list here
	this->list_problems = load_problems("data/options.txt");

	// generate problem
	problem generated_prob = gen_problem();

	// show problem
	show_problem(generated_prob);
}

// resume last saved game
void game::resume_game() {
	// load three game values from our simple datastore
	save my_save = load_save();

	if (my_save.g_game_state() == 1) {
		// game is lost
		start_game();
		return;
	}

	this->court = my_save.g_court();
	this->people = my_save.g_people();
	this->tresury = my_save.g_treasury();

	// populate the list
	this->list_problems = my_save.g_list_problems();

	// add all problems from datastore into the linked list also give them a random lifeCycle value
	problem new_problem = gen_problem();
	show_problem(new_problem);
}

// save current status of game
void game::save_game() {
	// save player name 
	// save if game was ended
	// save three game values
	ofstream ofile;
	ofile.open("data/save.txt");
	ofile << "player=" << this->main_player.g_pname() << endl;

	list<problem> list_problems = this->list_problems;

	string indices = "indices=";
	for (int i = 0; i < list_problems.size(); i++)
	{
		problem my_problem = list_problems[i];
		indices += to_string(my_problem.g_index()) + ",";
	}

	indices = indices.substr(0, indices.size() - 1);

	ofile << indices << endl;

	ofile << "people=" << this->people << endl;
	ofile << "court=" << this->court << endl;
	ofile << "tresury=" << this->tresury << endl;

	ofile << "state=" << this->game_state << endl;
	ofile.close();
}

// exit game
void game::exit_game() {
	cout << "Good bye!";
	exit(EXIT_SUCCESS);
}

// add effects
void game::effect(problem::option option) {
	this->people += option.g_effect_people();
	this->court += option.g_effect_court();
	this->tresury += option.g_effect_treasury();

	if (this->people > 100) {
		this->people = 100;
	}
	if (this->court > 100) {
		this->court = 100;
	}
	if (this->tresury > 100) {
		this->tresury = 100;
	}

	if (this->people < 0) {
		this->game_state = 1;
		this->people = 0;
	};
	if (this->court < 0) {
		this->game_state = 1;
		this->court = 0;
	}
	if (this->tresury < 0) {
		this->game_state = 1;
		this->tresury = 0;
	}

	/*cout << "people::" << this->people << endl;
	cout << "court::" << this->court << endl;
	cout << "treasury::" << this->tresury << endl;*/
}

problem game::gen_problem() {
	// get random index then random problem out of it
	int size = this->list_problems.size() - 1;
	// if we still have items in the list
	if (size > 0) {

		int rand_index = gen_rand_number(0, size);

		problem rand_problem = this->list_problems.get(rand_index);

		// if we still have life cycle remove one from it else remove it from the list
		if (rand_problem.g_life() < 1) {
			this->list_problems.remove(rand_index);

			// recursive call
			gen_problem();
		}
		else
		{
			/*cout << "random index ::::::: " << randomIndex << endl;
			cout << "random problem :::::: " << randomProblem.getTitle() << endl;
			cout << "lifecycle ::::::: " << randomProblem.getLifeCycle() << endl;*/

			int next_life = rand_problem.g_life() - 1;
			rand_problem.s_life(next_life);

			// modify list
			//cout << "before remove ::::::::" << this->problemsList.size() << endl;
			this->list_problems.remove(rand_index);
			//cout << "after remove ::::::::" << this->problemsList.size() << endl;

			// if it's last lifecycle no need to add it back
			if (next_life > 0)
				this->list_problems.insert(rand_index + 1, rand_problem);
			/*cout << "after inserts ::::::::" << this->problemsList.size() << endl;

			cout << "LIST:::::::::::::::::::::" << endl;

			for (int i = 0; i < this->problemsList.size(); i++)
			{
				cout << "list item:: " << this->problemsList[i].getTitle() << endl;
			}

			cout << "::::::::::::::::::::::::::" << endl;*/
		}

		return rand_problem;
	}

	// populate the list
	this->list_problems = load_problems("data/options.txt");

	return gen_problem();
}

// show problem
void game::show_problem(problem v_problem) {
	bool wrong_select = false;

	do
	{
		int user_input = 0;

		// first show the title
		cout << v_problem.g_title() << endl;

		// show option1
		cout << "[1] " << v_problem.g_option1().g_title() << endl;

		// show option2
		cout << "[2] " << v_problem.g_option2().g_title() << endl;

		// listen for input
		cin >> user_input;

		problem prob = gen_problem();


		// generator return empty
		//if (prob.getTitle() == "") break;

		switch (user_input)
		{
		case 1:
		{
			//cout << "option 1 was selected" << endl;

			// option 1 was selected effect the option

			problem::option option1 = prob.g_option1();
			// add the effects
			effect(option1);

			// check if we lost
			if (this->game_state == 1) {
				// we lost 
				cout << "game over" << endl;
				//exit(EXIT_SUCCESS);
				init();
				break;
			}

			// show the next problem
			show_problem(prob);
			wrong_select = false;
			break;
		}
		case 2:
		{
			//cout << "option 2 was selected" << endl;

			// option 2 was selected effect the option

			problem::option option2 = prob.g_option2();
			// add the effects
			effect(option2);

			// check if we lost
			if (this->game_state == 1) {
				// we lost 
				cout << "game over" << endl;
				init();
				break;
			}

			// show the next problem
			show_problem(prob);
			wrong_select = false;
			break;
		}
		case -1:
			// handle exit here
			// save before exit

			char option_select;
			cout << "do you want to save your game?(y/n) ";

			cin >> option_select;
			option_select = tolower(option_select);
			switch (option_select)
			{
			case 'y':
				save_game();
				exit_game();
				break;
			case 'n':
				exit_game();
				break;
			default:
				save_game();
				exit_game();
				break;
			}
		default:
			cout << "wrong option please slect one out of two or write -1 to exit";
			wrong_select = true;
			break;
		}
	} while (wrong_select);
}

// load save
save game::load_save() {
	list<string> lines = list<string>();

	ifstream fin;
	fin.open("data/save.txt");

	if (!fin) {
		cerr << "unabled to open file stream";

		exit(EXIT_FAILURE);
	}

	string line;
	save my_save = save();

	// my key pair list
	list<pair<string, string>> key_pairs = list<pair<string, string>>();

	while (getline(fin, line)) {
		lines.add(line);
		int del_pos = line.find("=");
		string key = line.substr(0, del_pos);
		string value = line.substr(del_pos + 1);

		// add key-pair to the list
		key_pairs.add(pair<string, string>(key, value));
	}

	fin.close();

	// populate save object

	// player
	player my_player = player();
	my_player.s_pname(key_pairs[0].second);
	my_save.s_main_player(my_player);

	// problem list
	string indices = key_pairs[1].second;

	// split string
	indices.replace(indices.begin(), indices.end(), ',', ' ');  // replace ':' by ' '

	list<int> list_indices = list<int>();
	stringstream ss(indices);
	int temp;
	while (ss >> temp)
		list_indices.add(temp);

	list<problem> list_problems = load_problems("data/options.txt");
	for (int i = 0; i < list_indices.size(); i++)
	{
		list_problems.remove(list_indices[i]);
	}

	my_save.s_list_problems(list_problems);

	// people
	string people = key_pairs[2].second;
	my_save.s_people(stoi(people));

	// court
	string court = key_pairs[3].second;
	my_save.s_court(stoi(court));

	// treasury
	string treasury = key_pairs[4].second;
	my_save.s_treasury(stoi(treasury));

	// game state
	string game_state = key_pairs[5].second;
	my_save.s_game_state(stoi(game_state));

	return my_save;
}

// getter and setters

// player
void game::s_player(player value) {
	this->main_player = value;
}
player game::g_player() {
	return this->main_player;
}

// game state
void game::s_game_state(int value) {
	this->game_state = value;
}
int game::g_game_state() {
	return this->game_state;
}

// people
void game::s_people(int value) {
	this->people = value;
}
int game::g_people() {
	return this->people;
}

// court
void game::s_court(int value) {
	this->court = value;
}
int game::g_court() {
	return this->court;
}

// treasury
void game::s_treasury(int value) {
	this->tresury = value;
}
int game::g_treasury() {
	return this->tresury;
}

// problem list
void game::s_list_problems(list<problem> value) {
	this->list_problems = value;
}
list<problem> game::g_list_problems() {
	return this->list_problems;
}



