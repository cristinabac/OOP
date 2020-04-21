#pragma once
#include "dynamicVector.h"
#include "Dog.h"
#include <vector>

class AdoptionList
{

private:
	std::vector<Dog> user_dogs;
	std::vector<Dog> all_dogs;
	int current;

public:
	AdoptionList();
	~AdoptionList();

	void add_al(const Dog &d);
	int find_by_name_al(std::string name);
	void add_to_adoption_list(const Dog &d);
	Dog get_current_dog();
	void start();
	void next();
	int is_empty();
	void clear_adoption_list();

	std::vector<Dog> get_user_dogs() const { return user_dogs; };
	std::vector<Dog> get_all_dogs() const { return all_dogs; };


};

