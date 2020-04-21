#pragma once
#include "Controller.h"
class Ui
{
private:
	Controller controller;

public:
	Ui(const Controller& c) : controller(c) {}
	~Ui();


	void add_dog_ui();
	void remove_dog_ui();
	void update_dog_ui();
	void print_all();

	void start();

};

