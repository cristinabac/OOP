#include "Ui.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;





Ui::~Ui()
{
}

int get_int(int min, std::string prompt)
{
	int ret_integer;
	std::string str_number;

	while (true) {

		std::cout << prompt;
		std::getline(std::cin, str_number); //get string input
		std::stringstream convert(str_number); //turns the string into a stream

		//checks for complete conversion to integer and checks for minimum value
		if (convert >> ret_integer && !(convert >> str_number) && ret_integer >= min) return ret_integer;

		std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
		std::cerr << "Input must be an integer >= " << min << ". Please try again.\n";
	}
}


void Ui::add_dog_ui()
{
	//int age;
	string breed, name, photo;

	cout << " Give breed: ";
	cin >> breed;
	cout << " Give name: ";
	cin >> name;
	//cout << " Give age: ";
	//cin >> age;
	int age = get_int(1, "Give age: ");
	cout << " Give link: ";
	cin >> photo;
	if (this->controller.add_dog_controller(breed, name, age, photo) == -1)
		cout << "This name already exists" << "\n";
	else
		cout << " Dog added :)" << "\n";

}

void Ui::remove_dog_ui()
{
	string name;
	cout << " Give name: ";
	cin >> name;
	if (this->controller.remove_dog_controller(name) == -1)
		cout << "There is no dog with that name" << "\n";
	else
		cout << " Dog removed :) " << "\n";
}

void Ui::update_dog_ui()
{
	//int age;
	string breed, name, photo;

	cout << " Give breed: ";
	cin >> breed;
	cout << " Give name: ";
	cin >> name;
	//cout << " Give age: ";
	//cin >> age;
	int age = get_int(1, "Give age: ");
	cout << " Give link: ";
	cin >> photo;
	if (this->controller.update_dog_controller(breed, name, age, photo) == -1)
		cout << "This name does not exist" << "\n";
	else
		cout << " Dog updated :)" << "\n";
}

void Ui::print_all()
{
	for (int i = 0; i < this->controller.get_repo().get_size_repo(); i++)
	{
		Dog actual_dog = this->controller.get_repo().get_all_dogs()[i];
		cout << " Breed: " << actual_dog.getBreed() << "     Name: " << actual_dog.getName() << "     Age: " << actual_dog.getAge() << "     Photo link:" << actual_dog.getPhoto() << "\n";
	}
}

void Ui::start()
{
	while (1 == 1)
	{
		int mode;
		cout << "0. Exit \n";
		cout << "1. Admin mode \n";
		cout << "2. User mode \n";
		cout << "Choose mode: ";
		cin >> mode;
		if (mode == 0)
			break;

		if (mode == 1)
			while(true)
			{
				cout << "0. Back" << "\n";
				cout << "1. Add dog" << "\n";
				cout << "2. Delete dog" << "\n";
				cout << "3. Update dog" << "\n";
				cout << "4. Display all dogs" << "\n";

				char cmd;
				cout << "Enter your command: ";
				cin >> cmd;
				cout << "\n";

				if (cmd == '4')
					this->print_all();

				if (cmd == '1')
					this->add_dog_ui();

				if (cmd == '2')
					this->remove_dog_ui();

				if (cmd == '3')
					this->update_dog_ui();

				if (cmd == '0')
					break;
			}

		if (mode == 2)
		{
			this->controller.get_adoption_list().clear_adoption_list();
			//std::string breed;
			char breed[50];
			cout << "Give the breed(nothing for all dogs): ";
			//cin >> breed;
			//getline(std::cin, breed);

			_fgetchar();
			gets_s(breed);

			int age = get_int(1, "Give age: ");

			this->controller.add_dogs_to_adoption_list_by_breed(breed,age);

			if (this->controller.get_adoption_list().is_empty() == 1)
			{
				cout << "No dogs :( \n";
			}
			else
			{
				this->controller.start_adoption_list();
				Dog current_dog = this->controller.get_adoption_list().get_current_dog();
				cout << "You are viewing the dog: \n";
				cout << " Breed: " << current_dog.getBreed() << "     Name: " << current_dog.getName() << "     Age: " << current_dog.getAge() << "\n";

				while (true)
				{
					cout << "0. Back \n";
					cout << "1. Adopt this dog \n";
					cout << "2. See next dog \n";
					cout << "3. Display your adoptions \n";
					int cmd;
					cout << "Enter your command: ";
					cin >> cmd;
					if (cmd == 0)
						break;
					if (cmd == 1)
					{
						//empty?
						Dog d = this->controller.get_adoption_list().get_current_dog();
						this->controller.adopt_dog(d);
					}
					if (cmd == 2)
					{
						this->controller.next_adoption_list();
						if (this->controller.get_adoption_list().get_all_dogs().size() == 0)
							cout << "No more dogs";
						else
						{
							Dog dog = this->controller.get_adoption_list().get_current_dog();
							cout << "You are viewing the dog: \n";
							cout << " Breed: " << dog.getBreed() << "     Name: " << dog.getName() << "     Age: " << dog.getAge() << "\n";
						}

					}
					if (cmd == 3)
					{
						vector<Dog> dv = this->controller.get_adoption_list().get_user_dogs();
						cout << "Your adoptions are: \n";
						if (dv.size() == 0)
							cout << "Your adoptions list is empty \n";
						for (int j = 0; j < dv.size(); j++)
						{
							Dog d = dv[j];
							cout << " Breed: " << d.getBreed() << "     Name: " << d.getName() << "     Age: " << d.getAge() << "\n";
						}
					}
				}

			}

		}

	}

}
