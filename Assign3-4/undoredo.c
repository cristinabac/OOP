#include "undoredo.h"
#include <string.h>


Operation* create_operation(Offer* o, char* name)
{
	Operation* oper = (Operation*)malloc(sizeof(Operation));
	oper->offer = copy_offer(o);

	if (name != NULL)
	{
		oper->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
		strcpy_s(oper->name, strlen(name)+1, name);
	}
	else
		oper->name = NULL;

	return oper;

}
void destroy_operation(Operation* oper)
{
	if (oper == NULL)
		return;
	destroy_offer(oper->offer);
	free(oper->name);
	free(oper);
}
Operation* copy_operation(Operation*oper)
{
	if (oper == NULL)
		return;

	Operation* new = create_operation(oper->offer, oper->name);
	return new;
}





OperationsList* create_operations_list()
{
	OperationsList* ol = (OperationsList*)malloc(sizeof(OperationsList));
	ol->length = 0;
	return ol;
}
void destroy_operations_list(OperationsList* ol)
{
	if (ol == NULL)
		return;
	for (int i = 0; i < ol->length; i++)
	{
		destroy_operation(ol->operations[i]);
	}
	free(ol);
}
void push(OperationsList* ol, Operation* oper)
{
	ol->operations[ol->length ++] = copy_operation(oper);
}
Operation* pop(OperationsList* ol)
{
	if (ol->length == 0)
		return NULL;
	ol->length--;
	return ol->operations[ol->length];
}