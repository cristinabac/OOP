#pragma once
#include "controller.h"


typedef struct {
	Controller* controller;
}Ui;

Ui* create_ui(Controller*);
void destroy_ui(Ui*);

void start_app(Ui*);

int add_ui(Ui*);
void delete_ui(Ui* ui);
int update_ui(Ui* ui);


void print_all_offers(Ui* ui);
