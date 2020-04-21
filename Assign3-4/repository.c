#include "repository.h"
#include "domain.h"
#include "dynamicArray.h"
#include <string.h>
#include<stdlib.h>
#include<stdio.h>

Repo* create_repo()
{
	/*
	Creates a repository
	output: repo - Repo (struct)
	*/

	Repo* r = (Repo*)malloc(sizeof(Repo));
	r->offers = createArray(2, &destroy_offer, &copy_offer);
	return r;
}


void destroy_repo(Repo* r)
{
	/*
	Destroys a repo
	Input: r - Repo
	*/
	if (r == NULL)
		return;

	destroyArray(r->offers);
	free(r);
}


int get_repo_len(Repo* r)
{
	/*
	Return the length of a repo
	Input: r - Repo
	*/
	return get_size(r->offers);
}


Offer* get_offer_by_position(Repo* r, int pos)
{
	/*
	Get the offer on a given position in the repository
	Input: r - Repo
		   pos - int
	Output: NULL - if the position is not in the array or if the repo is null
			Offer - otherwise
	*/
	if (r == NULL)
		return NULL;
	if (pos < 0 || pos >= get_repo_len(r))
		return NULL;
	return get_by_position(r->offers, pos);
}


int find_offer_by_address(Repo* r, char* address)
{
	/*
	Finds an offer by its address
	Input: r - Repo
		   address - char
	Output: pos - int - the position (if an offer with that address is found)
			-1 if there is no offer with that address
	*/
	int i;
	for (i = 0; i < get_repo_len(r); i++)
	{
		Offer* o = get_by_position(r->offers, i);
		char* o_address = get_address(o);
		if (strcmp(o_address, address) == 0) {
			free(o_address);
			return i;
		}
		free(o_address);
	}
	
	return -1;
}

int add_offer(Repo* r, Offer* o)
{
	/*
	Adds an offer in the repo
	Input: r  -Repo
		   o - Offer
	Output: 1 for succes, 0 otherwise
	*/
	if (r == NULL)
		return 0;

	if (find_offer_by_address(r, o->address) != -1)
		return 0;

	addToArray(r->offers, o);
	return 1;
}

int delete_offer_by_address(Repo*r, char* address)
{
	/*
	Delete an offer from repo
	Input: r - Repo
			address - char
	Output: 1 for succes, 0 otherwise
	*/
	int pos = find_offer_by_address(r, address);
	if (pos == -1)
		return 0;
	Offer* o = get_by_position(r->offers, pos);
	destroy_offer(o);
	delete_from_array(r->offers, pos);
	return 1;

}

int update_offer(Repo* r, Offer* o)
{
	/*
	Update an offer in the repo
	Input: r - Repo
		   o - Offer
	Output: 1 for succes, 0 otherwise
	*/
	int pos;
	pos = find_offer_by_address(r, o->address);
	if (pos == -1)
		return 0;
	destroy_offer(get_offer_by_position(r, pos));
	Offer* copy = copy_offer(o);
	update_in_array(r->offers, pos, copy);
	return 1;
}


