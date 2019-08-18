#include "pch.h"
#include "storage.h"

#include <fstream>

// check for saved file
bool check_save() {
	ifstream fin;
	fin.open("data/save.txt");

	return fin ? true : false;
}

// read a file and return all of the lines as a list
list<string> get_lines(string path) {

	list<string> list_lines = list<string>();

	ifstream fin;
	fin.open(path);

	if (!fin) {
		cerr << "unabled to open file stream";

		exit(EXIT_FAILURE);
	}

	string line;

	while (getline(fin, line)) {
		list_lines.add(line);
	}

	fin.close();

	return list_lines;
}

// load all data in options.txt file and store it into a list
list<problem> load_problems(string storage_path) {

	// problems list
	list<problem> list_problems = list<problem>();

	ifstream fin;
	fin.open(storage_path);


	if (!fin) {
		cerr << "unabled to open file stream";
		exit(EXIT_FAILURE);
	}

	string line;
	int counter = 0;

	while (getline(fin, line)) {

		problem my_problem = problem();

		// each line is file containing options
		list<string> lines_problem = get_lines("data/" + line);

		// as said in the project instructions
		// first line is title
		// second line is option1
		// 3,4,5 lines are effects on the three game values
		// 6th line is option2
		// 7,8,9 lines are effects on the three game values
		my_problem.s_index(counter);
		my_problem.s_title(lines_problem[0]);

		// option1
		problem::option option1 = problem::option();
		// option 1 title
		option1.s_title(lines_problem[1]);
		//cout << "debug " << option1.getTitle() << endl;

		// option 1 effects
		option1.s_effect_people(stoi(lines_problem[2]));
		option1.s_effect_court(stoi(lines_problem[3]));
		option1.s_effect_treasury(stoi(lines_problem[4]));

		problem::option option2 = problem::option();
		// option 2 title
		option2.s_title(lines_problem[5]);

		// option 2 effects
		option2.s_effect_people(stoi(lines_problem[6]));
		option2.s_effect_court(stoi(lines_problem[7]));
		option2.s_effect_treasury(stoi(lines_problem[8]));

		// setting options
		my_problem.s_option1(option1);
		my_problem.s_option2(option2);

		// default value
		my_problem.s_life(3);

		// add problem to the list
		list_problems.add(my_problem);

		++counter;
	}

	fin.close();

	return list_problems;

}



