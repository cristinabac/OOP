#include "Controller.h"



int Controller::add_dog_controller(const std::string breed, const std::string name, int age, const std::string photo)
{
	Dog d{ breed,name,age,photo };
	if (this->repo.add_dog(d) == 1)
		return 1;
	return -1;
}

int Controller::remove_dog_controller(const std::string name)
{
	if (this->repo.remove_dog(name) == 1)
		return 1;
	return -1;
}

int Controller::update_dog_controller(const std::string breed, const std::string name, int age, const std::string photo)
{
	Dog d{ breed,name,age,photo };
	if (this->repo.update_dog(d) == 1)
		return 1;
	return -1;
}

void Controller::add_dog_to_adoption_list(const Dog & d)
{
	this->adoptionList.add_al(d);
}

void Controller::start_adoption_list()
{
	this->adoptionList.start();
}

void Controller::next_adoption_list()
{
	this->adoptionList.next();
}

void Controller::adopt_dog(const Dog & d)
{
	this->adoptionList.add_to_adoption_list(d);
	this->repo.remove_dog(d.getName());
}

void Controller::add_dogs_to_adoption_list_by_breed(const std::string breed, int age)
{
	/*adds dogs having a certain breed to the adoption list
	if the string breed is empty, adds all with age <= *age*
	*/
	std::vector<Dog> foo = this->repo.get_all_dogs();
	std::vector<Dog> bar(foo.size());
	if (breed == "")
	{
		// copy only dogs with age less or equal to "age":
		auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [age](Dog d) {return d.getAge()<=age; });
		bar.resize(std::distance(bar.begin(), it));

	}
	else
	{
		// copy only dogs with breed "breed" with age less or equal to "age":
		auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [age,breed](Dog d) {return d.getBreed() == breed && d.getAge() <= age; });
		bar.resize(std::distance(bar.begin(), it));
	}
	for (auto dog : bar)
		this->adoptionList.add_al(dog);
}

Controller::~Controller()
{
}
