#pragma once
#include "Repo.h"
#include "AdoptionList.h"
#include "FileAdoptionList.h"
#include "DogValidator.h"
#include <algorithm>
#include <string.h>

class Controller
{
private:
	Repo repo;
	FileAdoptionList* adoptionList;
	DogValidator validator;

public:
	Controller(const Repo &r, FileAdoptionList* fal, DogValidator v) : repo{ r }, adoptionList{ fal }, validator{ v } {}

	Repo get_repo() const { return repo; }

	void add_dog_controller(const std::string breed, const std::string name, int age, const std::string photo);
	void remove_dog_controller(const std::string name);
	void update_dog_controller(const std::string breed, const std::string name, int age, const std::string photo);

	void add_dog_to_adoption_list(const Dog& d);
	void start_adoption_list();
	void next_adoption_list();
	void adopt_dog(const Dog& d);

	void add_dogs_to_adoption_list_by_breed(const std::string breed, int age);

	std::vector<Dog> find_str_in_breed(std::string breed);

	FileAdoptionList* get_adoption_list() const { return adoptionList; }


	~Controller();
};

