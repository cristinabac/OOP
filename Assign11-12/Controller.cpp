#include "Controller.h"



void Controller::add_dog_controller(const std::string breed, const std::string name, int age, const std::string photo)
{
	/*
	Add a dog
	Throws: DogException - if the dog is not valid
			RepositoryException - if the dog name already exists
	*/
	Dog d{ breed,name,age,photo };
	this->validator.validate(d);
	this->repo.add_dog(d);
}

void Controller::remove_dog_controller(const std::string name)
{
	/*
	Removes a dog from the list of dogs
	Throws: RepositoryException - if the dog name doesn t exist
	*/
	this->repo.remove_dog(name);
}

void Controller::update_dog_controller(const std::string breed, const std::string name, int age, const std::string photo)
{
	/*
	Updates  a dog by name
	Throws: DogException - if the new dog is not valid
			RepositoryException - if the dog name doesn t exist
	*/
	Dog d{ breed,name,age,photo };
	this->validator.validate(d);
	this->repo.update_dog(d);
}

void Controller::add_dog_to_adoption_list(const Dog & d)
{
	this->adoptionList->add_al(d);
}

void Controller::start_adoption_list()
{
	this->adoptionList->start();
}

void Controller::next_adoption_list()
{
	this->adoptionList->next();
}

void Controller::adopt_dog(const Dog & d)
{
	this->adoptionList->add_to_adoption_list(d);
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
		auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [age](Dog d) {return d.getAge() <= age; });
		bar.resize(std::distance(bar.begin(), it));

	}
	else
	{
		// copy only dogs with breed "breed" with age less or equal to "age":
		auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [age, breed](Dog d) {return d.getBreed() == breed && d.getAge() <= age; });
		bar.resize(std::distance(bar.begin(), it));
	}
	for (auto dog : bar)
		this->adoptionList->add_al(dog);
}

std::vector<Dog> Controller::find_str_in_breed(std::string breed)
{
	std::vector<Dog> vct;
	for (auto s : this->repo.get_all_dogs())
	{
		if (strstr(s.getBreed().c_str(), breed.c_str()) != NULL)
			vct.push_back(s);
	}
	return vct;
}

Controller::~Controller()
{
}
