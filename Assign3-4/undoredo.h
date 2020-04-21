#pragma once
#include "domain.h"
#include"dynamicArray.h"


typedef struct {
	Offer* offer;
	char* name;
}Operation;

Operation* create_operation(Offer*, char*);
void destroy_operation(Operation*);
Operation* copy_operation(Operation*);


typedef struct {
	Operation* operations[100];
	int length;
}OperationsList;

OperationsList* create_operations_list();
void destroy_operations_list(OperationsList*);
void push(OperationsList*, Operation*);
Operation* pop(OperationsList*);