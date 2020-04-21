#pragma once
#include "domain.h"
#include "repository.h"
#include "dynamicArray.h"
#include "undoredo.h"

typedef struct {
	Repo* repo;
	OperationsList* undoList;
	OperationsList* redoList;
}Controller;

Controller* create_controller(Repo *r, OperationsList*, OperationsList*);
void destroy_controller(Controller *c);

int add_offer_ctrl(Controller * ctrl, char *type, char *address, double surface, double price);
int delete_offer_ctrl(Controller * ctrl, char *address);
int update_offer_ctrl(Controller * ctrl, char *type, char *address, double surface, double price);

Repo* filter_by_address(Controller*c, char *address);
Repo* filter_by_type(Repo* r, char *type);
Repo* filter_by_surface_grater(Controller*c, double surface);

int undo(Controller* c);
int redo(Controller* c);

void sort_by_price(Repo* r);

Repo* filter_by_surface(Controller*c, double surface);
