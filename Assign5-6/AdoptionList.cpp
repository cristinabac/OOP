#include "AdoptionList.h"



AdoptionList::AdoptionList()
{
	this->current = 0;
}


AdoptionList::~AdoptionList()
{
}

void AdoptionList::add_al(const Dog & d)
{
	/*
	Adds a dog in the list of all dogs
	*/
	this->all_dogs.push_back(d);
}

int AdoptionList::find_by_name_al(std::string name)
{
	/*
	Finds the position of the dog with the name -name- in the list of all dogs
	Returns -1 if a dog with that name does not exist
	*/
	Dog d{};
	for (auto dog : this->all_dogs)
	{
		if (dog.getName() == name)
			d = dog;
	}
	if (d.getName() == "")
		return -1;
	int pos = std::find(this->all_dogs.begin(), this->all_dogs.end(), d) - this->all_dogs.begin();
	return pos;
}

void AdoptionList::add_to_adoption_list(const Dog & d)
{
	/*
	Adds a dog to the user s adoption list and removes it from the list of all dogs
	*/
	int pos = this->find_by_name_al(d.getName());
	this->user_dogs.push_back(d);
	this->all_dogs.erase(this->all_dogs.begin() + pos);
}

Dog AdoptionList::get_current_dog()
{
	if (this->current == this->all_dogs.size())
		this->current = 0;
	/*
	std::vector<Dog>* dogs = this->all_dogs.getAllElems();
	if (dogs != NULL)
		return dogs[this->current];
	*/
	if(this->all_dogs.size() != 0)
		return this->all_dogs[this->current];
	return Dog{};
}

void AdoptionList::start()
{
	/*display the current dog
	*/
	if (this->all_dogs.size() == 0)
		return;
	Dog currentDog = this->get_current_dog();
	currentDog.show();
}

void AdoptionList::next()
{
	/*display the dog on the next position
	*/
	if (this->all_dogs.size() == 0)
		return;
	this->current++;
	Dog currentDog = this->get_current_dog();
	currentDog.show();
}

int AdoptionList::is_empty()
{
	/*Verifies if the list of all dogs is empty
	Returns 1 if it is empty, 0 otherwise
	*/
	return this->all_dogs.size() == 0;
}

void AdoptionList::clear_adoption_list()
{
	/*
	*/
	while (!this->is_empty())
		this->all_dogs.erase(this->all_dogs.begin());
}
