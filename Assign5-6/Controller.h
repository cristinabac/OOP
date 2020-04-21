#pragma once
#include "Repo.h"
#include "AdoptionList.h"
#include <algorithm>

class Controller
{
private:
	Repo repo;
	AdoptionList adoptionList;

public:
	Controller(const Repo &r): repo{r}{}

	Repo get_repo() const { return repo; }

	int add_dog_controller(const std::string breed, const std::string name, int age, const std::string photo);
	int remove_dog_controller(const std::string name);
	int update_dog_controller(const std::string breed, const std::string name, int age, const std::string photo);

	void add_dog_to_adoption_list(const Dog& d);
	void start_adoption_list();
	void next_adoption_list();
	void adopt_dog(const Dog& d);

	void add_dogs_to_adoption_list_by_breed(const std::string breed, int age);

	AdoptionList get_adoption_list() const { return adoptionList; }


	~Controller();
};

