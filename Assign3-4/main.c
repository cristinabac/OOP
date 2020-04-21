#define _CRTDBG_MAP_ALLOC
#include "domain.h"
#include "dynamicArray.h"
#include "repository.h"
#include "controller.h"
#include "ui.h"
#include <stdlib.h>
#include <crtdbg.h>
#include<assert.h>
#include<Windows.h>

void test_offer()
{
	Offer* o = create_offer("house", "No address", 2000, 25);
	char* type = get_type(o);
	assert(strcmp(type, "house") == 0);
	free(type);
	char* address = get_address(o);
	assert(strcmp(address, "No address") == 0);
	free(address);
	double price = get_price(o);
	assert(price == 25);
	destroy_offer(o);
}

void test_DA()
{
	DynamicArray* da = createArray(2, &destroy_offer, &copy_offer);

	Offer* o1 = create_offer("house", "No address", 2000, 25);
	Offer* o2 = create_offer("apartament", "Address 24, Cluj", 3500, 47);
	addToArray(da,o1);
	addToArray(da, o2);

	assert(da->size == 2);
	assert(da->capacity == 2);

	Offer* o3 = create_offer("penthouse", "Strada abc, 34", 1234, 55);
	addToArray(da,o3);
	assert(da->size == 3);
	assert(da->capacity == 4);  //2*previous capacity => 2*2=4

	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);
	destroyArray(da);
}

void test_repo()
{
	Repo* r = create_repo();
	assert(get_repo_len(r) == 0);
	
	Offer *o1 = create_offer("house", "str dorobantilor, 44", 55, 1234);
	assert(add_offer(r, o1) == 1);
	assert(get_repo_len(r) == 1);
	
	assert(add_offer(r, o1) == 0);
	assert(get_repo_len(r) == 1);

	Offer *o2 = create_offer("penthouse", "abc address 45", 70, 3000);
	assert(add_offer(r, o2) == 1);
	assert(get_repo_len(r) == 2);

	assert(delete_offer_by_address(r, "str") == 0);
	assert(get_repo_len(r) == 2);

	assert(delete_offer_by_address(r, "str dorobantilor, 44") == 1);
	assert(get_repo_len(r) == 1);

	assert(delete_offer_by_address(r, "str dorobantilor, 44") == 0);
	assert(get_repo_len(r) == 1);

	assert(strcmp((get_offer_by_position(r, 0))->type, "penthouse") == 0);
	assert((get_offer_by_position(r, 0))->surface == 70);

	Offer *o3 = create_offer("apartment", "abc address 45", 64, 80000);
	assert(update_offer(r, o3) == 1);
	assert(strcmp((get_offer_by_position(r, 0))->type, "apartment") == 0);
	assert((get_offer_by_position(r, 0))->surface == 64);

	Offer *o4 = create_offer("apartment", "str dorobantilor", 28, 700000);
	assert(update_offer(r, o4) == 0);
	
	
	destroy_offer(o1);
	destroy_offer(o2);
	destroy_offer(o3);
	destroy_offer(o4);
	destroy_repo(r);
	
}

void test_controller()
{
	Repo *r = create_repo();
	OperationsList* undoList = create_operations_list();
	OperationsList* redoList = create_operations_list();
	Controller *c = create_controller(r, undoList, redoList);

	assert(add_offer_ctrl(c, "house", "adresa 1", 66, 1000) == 1);
	assert(get_repo_len(c->repo) == 1);

	assert(add_offer_ctrl(c, "apartament", "adresa 2", 88, 1111) == 1);
	assert(get_repo_len(c->repo) == 2);

	assert(add_offer_ctrl(c, "house", "adresa 3", 70, 30000) == 1);
	assert(get_repo_len(c->repo) == 3);

	assert(add_offer_ctrl(c, "house", "adresa 2", 66, 1000) == 0); //not added
	assert(get_repo_len(c->repo) == 3);

	assert(delete_offer_ctrl(c, "adresa 2") == 1);
	assert(get_repo_len(c->repo) == 2);

	assert(delete_offer_ctrl(c, "adresa 2") == 0);
	assert(get_repo_len(c->repo) == 2);

	assert(update_offer_ctrl(c, "apartament", "adresa 3", 10, 10) ==1 );
	assert((get_offer_by_position(c->repo, find_offer_by_address(c->repo, "adresa 3")))->price == 10);

	assert(update_offer_ctrl(c, "apartament", "adresa 2", 10, 10) == 0);

	Repo* rr= filter_by_address(c, "adresa");
	assert(get_repo_len(rr) == 2);

	sort_by_price(rr);
	assert(strcmp(get_offer_by_position(rr, 0)->address,"adresa 3") ==0 );

	destroy_repo(rr);

	destroy_controller(c);
}

void initialize_offers(Controller * c)
{
	add_offer_ctrl(c, "house", "No address", 2000, 25);
	add_offer_ctrl(c,"apartament", "Address2", 350, 40);
	add_offer_ctrl(c,"apartament", "str abc", 3501, 50);
	add_offer_ctrl(c,"apartament", "str aaa", 3500, 70 );
	add_offer_ctrl(c,"penthouse", "cluj 22", 3500, 40);
	add_offer_ctrl(c,"penthouse", "str dorobantilor 23", 300, 20);
	add_offer_ctrl(c,"house", "cluj 23", 3500, 450);
	add_offer_ctrl(c,"penthouse", "Address 44", 3500, 405 );
	add_offer_ctrl(c,"apartament", "Address 445", 3500, 70 );
	add_offer_ctrl(c,"house", "Address 5", 3500, 35);
	add_offer_ctrl(c,"apartament", "Address 4", 3500, 7);
	add_offer_ctrl(c,"apartament", "Address lala", 3500, 700);
}

int main(int argc, char** argv)
{
	test_offer();
	test_DA();
	test_repo();
	test_controller();


	Repo* repository = create_repo();
	OperationsList* undoList = create_operations_list();
	OperationsList* redoList = create_operations_list();
	Controller* controller = create_controller(repository,undoList,redoList);
	Ui* ui = create_ui(controller);

	initialize_offers(controller);

	start_app(ui);
	destroy_ui(ui);

	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}