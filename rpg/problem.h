#pragma once
#include <string>

using namespace std;

class problem
{
public:
	// nested class
	class option
	{
	private:
		string title;
		int effect_people;
		int effect_court;
		int effect_treasury;
	public:
		// constructor #1
		option() {}

		// constructor #2
		option(string v_title, int v_effect_people, int v_effect_court, int v_effect_treasury) {
			title = v_title;
			effect_people = v_effect_people;
			effect_court = v_effect_court;
			effect_treasury = v_effect_treasury;
		}

		// getter and setters

		// title
		void s_title(string value) {
			title = value;
		}
		string g_title() {
			return title;
		}

		// effect on people
		void s_effect_people(int value) {
			effect_people = value;
		}
		int g_effect_people() { return effect_people; }

		// effect on court
		void s_effect_court(int value) {
			effect_court = value;
		}
		int g_effect_court() { return effect_court; }

		// effect on treasury
		void s_effect_treasury(int value) {
			effect_treasury = value;
		}
		int g_effect_treasury() { return effect_treasury; }
	};

	// constructor #1
	problem();

	// constructor #2
	problem(string, int, option, option);

	// functions
	void s_index(int);
	int g_index();

	// title
	void s_title(string);
	string g_title();

	// life cycle
	void s_life(int);
	int g_life();

	// option 1
	void s_option1(option);
	option g_option1();

	// option 2
	void s_option2(option);
	option g_option2();

private:
	int index;
	int life;
	string title;
	option option1;
	option option2;
};

