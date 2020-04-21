#include "dynamicArray.h"
#include <stdlib.h>

DynamicArray* createArray(int capacity, destroyFunction destroyF, copyFunction copyF)
{
	DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
	array->capacity = capacity;
	array->size = 0;
	array->data = (TElem*)malloc(sizeof(TElem)*capacity);

	array->destroyFct = destroyF;
	array->copyFct = copyF;

	return array;
}

void destroyArray(DynamicArray* array)
{
	if (array == NULL)
		return;

	for (int i = 0; i < array->size; i++)
		array->destroyFct(array->data[i]);

	free(array->data);
	free(array);
}

void addToArray(DynamicArray * array, TElem elementToAdd)
{
	if (array->size == array->capacity)
	{
		resize(array);
	}
	array->data[array->size++] = array->copyFct(elementToAdd);
}

void resize(DynamicArray * array)
{
	array->capacity *= 2;
	TElem* newElems = malloc(sizeof(TElem)*array->capacity);
	for (int i = 0; i < array->size; i++) {
		newElems[i] = array->data[i];
	}
	free(array->data);
	array->data = newElems;
}

DynamicArray * copyArray(DynamicArray * array)
{
	DynamicArray* newA = (DynamicArray*)malloc(sizeof(DynamicArray));
	newA->capacity = array->capacity;
	newA->size = array->size;
	newA->data = (TElem*)malloc(sizeof(TElem)*newA->capacity);

	newA->destroyFct = array->destroyFct;
	newA->copyFct = array->copyFct;

	for (int i = 0; i < array->size; i++)
		newA->data[i] = array->copyFct(array->data[i]);

	return newA;
}

int get_size(DynamicArray* da)
{
	/*
	Returns the size of a dynamic array
	Input: da - DynamicArray
	*/
	return da->size;
}

TElem get_by_position(DynamicArray* da, int pos)
{
	/*
	Get the element on a position in the array
	Input: da - DynamicArray
		   pos - int
	Output: TElem
	*/
	return da->data[pos];
}

void delete_from_array(DynamicArray* da, int pos)
{
	/*
	Delete the element on a given position
	Input: da - DynamicArray
			pos - int
	*/
	int i;

	if (da == NULL)
		return;

	if (da->data == NULL)
		return;

	if (pos < 0 || pos >= da->size)
		return;

	for (i = pos; i < da->size - 1; i++)
		da->data[i] = da->data[i + 1];
	da->size = da->size - 1;

}

void update_in_array(DynamicArray* da, int pos, TElem* e)
{
	/*
	Update the element on a position in the array - replace the elemet with a new one
	Input: da - DynamicArray
		   pos - int
		   e - element to update
	*/
	da->data[pos] = e;

}