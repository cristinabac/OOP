#pragma once
#include "domain.h"

typedef void* TElem;
typedef void(*destroyFunction)(TElem);
typedef TElem(*copyFunction)(TElem);

typedef struct {

	TElem* data;
	int size, capacity;
	destroyFunction destroyFct;
	copyFunction copyFct;

}DynamicArray;

DynamicArray* createArray(int capacity, destroyFunction destroyF, copyFunction copyF);

void destroyArray(DynamicArray* array);

void addToArray(DynamicArray* array, TElem elementToAdd);

void resize(DynamicArray* array);

void delete_from_array(DynamicArray*, int);

void update_in_array(DynamicArray*, int, TElem*);

int get_size(DynamicArray*);

TElem get_by_position(DynamicArray*, int);

DynamicArray* copyArray(DynamicArray* array);
