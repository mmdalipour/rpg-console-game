#include "pch.h"
#include "problem.h"


problem::problem() {

}

problem::problem(string title, int life, problem::option option1, problem::option option2)
{
	this->title = title;
	this->life = life;
	this->option1 = option1;
	this->option2 = option2;
}

// getter and setters

// index
void problem::s_index(int value) {
	this->index = value;
}
int problem::g_index() {
	return this->index;
}

// life
void problem::s_life(int value) {
	this->life = value;
}
int problem::g_life() {
	return this->life;
}

// title
void problem::s_title(string value) {
	this->title = value;
}
string problem::g_title() {
	return this->title;
}

// option1
void problem::s_option1(problem::option value) {
	this->option1 = value;
}
problem::option problem::g_option1() {
	return this->option1;
}

// option2
void problem::s_option2(problem::option value) {
	this->option2 = value;
}
problem::option problem::g_option2() {
	return this->option2;
}