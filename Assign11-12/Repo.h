#pragma once
//#include "dynamicVector.h"
#include "Dog.h"
#include <vector>

class Repo
{

private:
	std::vector<Dog> dogs;
	std::string filename;

public:

	void add_dog(const Dog& d);
	void remove_dog(const std::string& name);
	Dog find_by_name(const std::string& name);
	void update_dog(const Dog& d);

	int find_by_name_pos(const std::string& name);
	Dog get_elem_on_pos(int pos);

	std::vector<Dog> get_all_dogs() const { return this->dogs; }

	int get_size_repo() const;

	void read_from_file();
	void write_to_file();


	Repo(const std::string& filename);
};

