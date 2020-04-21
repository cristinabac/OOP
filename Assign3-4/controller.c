#include "controller.h"
#include "domain.h"
#include "repository.h"
#include "dynamicArray.h"
#include <string.h>


Controller* create_controller(Repo *r, OperationsList* undoList, OperationsList* redoList)
{
	/*
	Create controller
	*/
	Controller* ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl->repo = r;
	ctrl->undoList = undoList;
	ctrl->redoList = redoList;
	return ctrl;
}


void destroy_controller(Controller *c)
{
	destroy_repo(c->repo);
	destroy_operations_list(c->undoList);
	destroy_operations_list(c->redoList);
	free(c);
}


int add_offer_ctrl(Controller * ctrl, char *type, char *address, double surface, double price)
{
	/*
	Add an offer in the controller
	Input: ctrl - Controller
		  address, type - strings
		  surface,price - double
	Output:  1 in case of succes, 0 otherwise
	*/
	Offer *o = create_offer(type, address, surface, price);
	int res = add_offer(ctrl->repo, o);

	if (res == 1)
	{
		Operation* oper = create_operation(o, "add");
		push(ctrl->undoList, oper);
		destroy_operation(oper);
	}

	destroy_offer(o);
	return res;
}


int delete_offer_ctrl(Controller * ctrl, char *address)
{
	/*
	Delete an offer from the controller
	Input: ctrl - Controller
		  address - string
	Output:  1 in case of succes, 0 otherwise
	*/
	int pos = find_offer_by_address(ctrl->repo, address);
	Offer *old = copy_offer(get_offer_by_position(ctrl->repo, pos));

	int res = delete_offer_by_address(ctrl->repo, address);


	if (res == 1)
	{
		Operation* oper = create_operation(old, "delete");
		push(ctrl->undoList, oper);
		destroy_operation(oper);
	}

	destroy_offer(old);
	return res;
}


int update_offer_ctrl(Controller * ctrl, char *type, char *address, double surface, double price)
{
	/*
	Updates an offer in the controller - by the address
	Input: ctrl - Controller
		  address, type - strings
		  surface,price - double
	Output:  1 in case of succes, 0 otherwise
	*/
	Offer *new = create_offer(type, address, surface, price);
	int pos = find_offer_by_address(ctrl->repo, address);
	Offer * old = copy_offer(get_offer_by_position(ctrl->repo, pos));
	int res = update_offer(ctrl->repo, new);


	if (res == 1)
	{
		Operation* oper = create_operation(old, "update");
		push(ctrl->undoList, oper);
		destroy_operation(oper);
	}

	destroy_offer(new);
	destroy_offer(old);
	return res;
}



int undo(Controller* c)
{
	/*
	Undo the prev operation - add,delete or update
	Input: c - Controller
	Output: 1 for succes, 0 otherwise
	*/
	if (c->undoList->length == 0)
		return 0;

	Operation* oper = pop(c->undoList);

	if (strcmp(oper->name, "add") == 0)
	{
		Offer* o = oper->offer;
		push(c->redoList, oper);

		delete_offer_by_address(c->repo, o->address);
	}
	if (strcmp(oper->name, "delete") == 0)
	{
		Offer* o = oper->offer;
		push(c->redoList, oper);

		add_offer(c->repo, o);
	}
	if (strcmp(oper->name, "update") == 0)
	{
		Offer* o = oper->offer;

		int position = find_offer_by_address(c->repo, o->address);
		Offer* offer = get_offer_by_position(c->repo, position);
		Operation* operRedo = create_operation(offer, "update");
		push(c->redoList, operRedo);
		destroy_operation(operRedo);

		update_offer(c->repo, o);
	}
	destroy_operation(oper);
	return 1;
}


int redo(Controller* c)
{
	/*
	redo the prev operation - add,delete or update
	Input: c - Controller
	Output: 1 for succes, 0 otherwise
	*/
	if (c->redoList->length == 0)
		return 0;
	Operation* oper = pop(c->redoList);

	if (strcmp(oper->name, "add") == 0)
	{
		Offer* o = oper->offer;
		push(c->undoList, oper);

		add_offer(c->repo, o);
	}
	if (strcmp(oper->name, "delete") == 0)
	{
		Offer* o = oper->offer;
		push(c->undoList, oper);

		delete_offer_by_address(c->repo, o->address);
	}
	if (strcmp(oper->name, "update") == 0)
	{
		Offer* o = oper->offer;

		int position = find_offer_by_address(c->repo, o->address);
		Offer* offer = get_offer_by_position(c->repo, position);
		Operation* operUndo = create_operation(offer, "update");
		push(c->undoList, operUndo);
		destroy_operation(operUndo);

		update_offer(c->repo, o);
	}
	destroy_operation(oper);
	return 1;

}



Repo* filter_by_address(Controller*c, char *address)
{
	/*
	Filter by address
	Input: c- Controller
		   address - string, the substring to search
	Output: r - Repo - the filtered repo
	*/
	Repo *r = create_repo();
	int i;
	for (i = 0; i < get_repo_len(c->repo); i++)
	{
		if (strstr(get_offer_by_position(c->repo, i)->address, address) != 0)
		{
			Offer *o = get_offer_by_position(c->repo, i);
			add_offer(r, o);
		}

	}
	return r;
}

Repo* filter_by_surface(Controller*c, double surface)
{
	/*
	Filter by surface
	Input: c- Controller
		   surface - double
	Output: r - Repo - the filtered repo
	*/
	Repo *r = create_repo();
	int i;
	for (i = 0; i < get_repo_len(c->repo); i++)
	{
		if (get_offer_by_position(c->repo, i)->surface == surface)
		{
			Offer *o = get_offer_by_position(c->repo, i);
			add_offer(r, o);
		}

	}
	return r;
}


void sort_by_price(Repo* r)
{
	/*
	Sorts a given repo
	Input: r - Repo
	*/
	int i,j;

	for (i = 0; i < get_repo_len(r) - 1; i++)
		for (j = i + 1; j < get_repo_len(r); j++)
			if (get_offer_by_position(r,i)->price > get_offer_by_position(r, j)->price)
			{
				Offer *aux = get_offer_by_position(r, i);
				r->offers->data[i] = get_offer_by_position(r, j);
				r->offers->data[j] = aux;
			}

}

Repo* filter_by_type(Repo*r, char *type)
{
	/*
	Filter by type - returns elements having the given type
	Input: r - Repo
		   type - string
	Output: r - Repo - the filtered repo
	*/
	Repo *rr = create_repo();
	int i;
	for (i = 0; i < get_repo_len(r); i++)
	{
		if (strcmp(get_offer_by_position(r, i)->type, type) == 0)
		{
			Offer *o = get_offer_by_position(r, i);
			add_offer(rr, o);
		}

	}
	return rr;
}

Repo* filter_by_surface_grater(Controller*c, double surface)
{
	/*
	Filter by surface - returns repo with elements having surface grater than the given surface
	Input: c- Controller
		   surface - double
	Output: r - Repo - the filtered repo
	*/
	Repo *r = create_repo();
	int i;
	for (i = 0; i < get_repo_len(c->repo); i++)
	{
		if (get_offer_by_position(c->repo, i)->surface > surface)
		{
			Offer *o = get_offer_by_position(c->repo, i);
			add_offer(r, o);
		}

	}
	return r;
}