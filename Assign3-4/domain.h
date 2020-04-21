#pragma once


typedef struct {
	char *type;
	char* address;
	double surface, price;

}Offer;

Offer* create_offer(char*, char*, double, double);
Offer* copy_offer(Offer*);
void destroy_offer(Offer*);

char* get_type(Offer*);
char* get_address(Offer*);
double get_surface(Offer*);
double get_price(Offer*);









