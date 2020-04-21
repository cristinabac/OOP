#include "domain.h"
#include <string.h>
#include<stdlib.h>


Offer* create_offer(char* type, char* address, double surface, double price)
{
	/*
	Creates an offer
	Input: type - char
		   address - char
		   surface - double
		   price - double
	Output: offer - Offer (struct)
	*/
	Offer *o = (Offer*)malloc(sizeof(Offer));
	
	o->type = (char*)malloc(sizeof(char) * (strlen(type)+1));
	strcpy_s(o->type, strlen(type) + 1, type);

	o->address = (char*)malloc(sizeof(char) * (strlen(address)+1));
	strcpy_s(o->address, strlen(address)+1, address);

	o->surface = surface;;
	o->price = price;
	return o;
}


Offer* copy_offer(Offer* o)
{
	/*
	Makes a copy of an offer
	Input: o - offer
	Output: copy - the copy of the given offer
	*/
	if (o == NULL)
		return NULL;

	Offer* copy = (Offer*)malloc(sizeof(Offer));
	
	copy->type = (char*)malloc(sizeof(char) * (strlen(o->type) + 1));
	strcpy_s(copy->type, strlen(o->type) + 1, o->type);
	copy->address = (char*)malloc(sizeof(char) * (strlen(o->address) + 1));
	strcpy_s(copy->address, strlen(o->address) + 1, o->address);
	copy->surface = o->surface;
	copy->price = o->price;

	return copy;
}


void destroy_offer(Offer* o)
{
	/*
	Destroy a given offer(free from memory)
	Input: o - Offer
	*/
	if (o == NULL)
		return;
	
	free(o->type);
	free(o->address);
	free(o);
}

char* get_type(Offer*o)
{
	char *type = (char*)malloc(sizeof(char) * strlen(o->type) + 1);
	strcpy_s(type, strlen(o->type) + 1, o->type);
	return type;
}
char* get_address(Offer*o)
{
	char *address = (char*)malloc(sizeof(char) * strlen(o->address) + 1);
	strcpy_s(address, strlen(o->address) + 1, o->address);
	return address;
}
double get_surface(Offer*o)
{
	return o->surface;
}
double get_price(Offer*o)
{
	return o->price;
}
