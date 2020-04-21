#pragma once
#include "domain.h"
#include "dynamicArray.h"

typedef struct {
	DynamicArray* offers;
}Repo;

Repo* create_repo();
void destroy_repo(Repo*);

int get_repo_len(Repo*);

int find_offer_by_address(Repo*, char*);

int add_offer(Repo*, Offer*);

int delete_offer_by_address(Repo*, char*);

int update_offer(Repo*, Offer*);

Offer* get_offer_by_position(Repo*, int);
