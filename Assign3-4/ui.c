#include "ui.h"
#include <string.h>
#include<stdlib.h>
#include<stdio.h>

Ui* create_ui(Controller* c)
{
	Ui* ui = (Ui*)malloc(sizeof(Ui));
	ui->controller = c;
	return ui;
}

void destroy_ui(Ui* ui)
{
	destroy_controller(ui->controller);
	free(ui);
}


int add_ui(Ui* ui)
{
	char address[30], type[30];
	double surface, price;

	printf("Type (house, apartament or penthouse): ");
	scanf_s("%s", type, sizeof(type));
	if (strcmp(type, "house") != 0 && strcmp(type, "apartament") != 0 && strcmp(type, "penthouse") != 0)
		return -1; //invalid input

	printf("\n Address: ");
	//scanf_s("%10[0-9a-zA-Z ]", address, sizeof(address));
	_fgetchar();
	fgets(address, 30, stdin);
	address[strlen(address) - 1] = '\0';

	printf("\n Surface: ");
	scanf_s("%lf", &surface);
	if (surface <= 0) return -1;

	printf("\n Price: ");
	scanf_s("%lf", &price);
	if (price <= 0) return -1;

	return add_offer_ctrl(ui->controller, type, address, surface, price);

}

void print_offer(Offer *o)
{
	if (o!=NULL)
		printf("%11s  -  %30s  -  %10lf  -  %10lf \n", o->type, o->address, o->surface, o->price);
}

void print_all_offers(Ui* ui)
{
	int i;
	if (get_repo_len(ui->controller->repo) == 0)
	{
		printf("\n The list is empty \n");
	}
	else
	{
		printf("      TYPE                   ADDRESS                   SURFACE          PRICE \n");
		for (i = 0; i < get_repo_len(ui->controller->repo); i++)
		{
			print_offer(get_offer_by_position( ui->controller->repo,i));
		}
	}
}

void delete_ui(Ui* ui)
{
	char address[30];
	printf("The address: ");
	_fgetchar();
	fgets(address, 30, stdin);
	address[strlen(address) - 1] = '\0';

	if (delete_offer_ctrl(ui->controller, address) == 0)
		printf("\n The address does not exist \n");
}

int update_ui(Ui* ui)
{
	char address[30], type[30];
	double surface, price;

	printf("Type (house, apartament or penthouse): ");
	scanf_s("%s", type, sizeof(type));
	if (strcmp(type, "house") != 0 && strcmp(type, "apartament") != 0 && strcmp(type, "penthouse") != 0)
		return -1; //invalid input

	printf("\n Address: ");
	//scanf_s("%10[0-9a-zA-Z ]", address, sizeof(address));
	_fgetchar();
	fgets(address, 30, stdin);
	address[strlen(address) - 1] = '\0';

	printf("\n Surface: ");
	scanf_s("%lf", &surface);
	if (surface <= 0) return -1;

	printf("\n Price: ");
	scanf_s("%lf", &price);
	if (price <= 0) return -1;

	return update_offer_ctrl(ui->controller, type, address, surface, price);
}


void filter_by_address_ui(Ui* ui)
{
	char s[100];
	int i;
	Repo* rr;
	printf("The subString: ");
	_fgetchar();
	fgets(s, 99, stdin);

	if (strcmp(s, "\n") == 0)
	{
		rr = create_repo();
		for (i = 0; i < get_repo_len(ui->controller->repo); i++)
		{
			Offer *o = get_offer_by_position(ui->controller->repo, i);
			add_offer(rr, o);
		}
		sort_by_price(rr);
		for (i = 0; i < get_repo_len(rr); i++)
		{
			print_offer(get_offer_by_position(rr, i));
		}
		destroy_repo(rr);
	}
	else
	{
		s[strlen(s) - 1] = '\0';
		rr = filter_by_address(ui->controller, s);
		sort_by_price(rr);
		for (i = 0; i < get_repo_len(rr); i++)
		{
			print_offer(get_offer_by_position(rr, i));
		}
		destroy_repo(rr);
	}
	
}

void filter_by_surface_ui(Ui* ui)
{
	int i;
	double surface;
	printf("The surface: ");
	scanf_s("%lf", &surface);
	Repo* rr = filter_by_surface(ui->controller, surface);
	sort_by_price(rr);
	for (i = 0; i < get_repo_len(rr); i++)
	{
		print_offer(get_offer_by_position(rr, i));
	}
	destroy_repo(rr);
}

void pr_7(Ui* ui)
{
	int i;
	double surface;
	char type[30];
	printf("The surface: ");
	scanf_s("%lf", &surface);
	printf("The type: ");
	scanf_s("%s", type, sizeof(type));

	Repo* rr = filter_by_surface_grater(ui->controller, surface);	
	Repo *rrr = filter_by_type(rr, type);
	for (i = 0; i < get_repo_len(rrr); i++)
		{
			print_offer(get_offer_by_position(rrr, i));
		}
	destroy_repo(rr);
	destroy_repo(rrr);
}


void start_app(Ui* ui)
{
	int cmd;

	while (1 == 1)
	{
		printf("0. Exit \n");
		printf("1. Add an offer \n");
		printf("2. Delete an offer \n");
		printf("3. Update an offer \n");
		printf("4. Print all offers \n");
		printf("5. Display all offers whose address contains a given string, sorted ascending by their price \n");
		printf("6. For a given surface, display all offers, sorted ascending by price \n");
		printf("7. Display all offers of a given type, having the surface greater than a given value \n");
		printf("8. Undo \n");
		printf("9. Redo \n");
		printf("\n Enter your command: ");
		scanf_s("%d", &cmd);
		while (cmd < 0 || cmd>9)
		{
			printf("Invalid command! \n Enter new command: ");
			scanf_s("%d", &cmd);
		}
		switch (cmd)
		{
		case 0:
			return;

		case 1:
		{
			int res = add_ui(ui);
			if (res == -1)
				printf("\n Wrong input \n");
			else
				if (res == 0)
					printf("\n This address already exists \n");
			break;
		}

		case 2:
		{
			delete_ui(ui);
			break;
		}

		case 3:
		{
			int res = update_ui(ui);
			if (res == -1)
				printf("\n Wrong input \n");
			else
				if (res == 0)
					printf("\n This address does NOT exist \n");
			break;
		}

		case 4:
		{
			print_all_offers(ui);
			break;
		}

		case 5:
		{
			filter_by_address_ui(ui);
			break;
		}

		case 6:
		{
			filter_by_surface_ui(ui);
			break;
		}

		case 7:
		{
			pr_7(ui);
			break;
		}

		case 8:
		{
			int res = undo(ui->controller);
			if (res == 0)
				printf("\n\nNo more undos\n \n");
			break;
		}

		case 9:
		{
			int res = redo(ui->controller);
			if (res == 0)
				printf("\n \nNo more redos\n \n");
			break;
		}

		}
	}
}