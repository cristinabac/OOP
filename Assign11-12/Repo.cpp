#include "Repo.h"
#include <string.h>
#include <fstream>
#include "RepoExceptions.h"

void Repo::add_dog(const Dog& d)
{
	/*
	Adds a dog to the repo
	*/
	int pos = this->find_by_name_pos(d.getName());
	if (pos != -1)
		throw ExistingNameException();
	this->dogs.push_back(d);
	this->write_to_file();
}

int Repo::get_size_repo() const
{
	return this->dogs.size();
}

void Repo::read_from_file()
{
	std::ifstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be open!");

	Dog d;
	while (file >> d)
		this->dogs.push_back(d);
	file.close();
}

void Repo::write_to_file()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be open!");

	for (auto d : this->dogs)
		file << d;
	file.close();
}

Repo::Repo(const std::string & filename)
{
	this->filename = filename;
	this->read_from_file();
}

Dog Repo::find_by_name(const std::string& name)
{
	for (auto dog : this->dogs)
	{
		if (dog.getName() == name)
			return dog;
	}
	return Dog{};
}

void Repo::remove_dog(const std::string& name)
{
	int pos = this->find_by_name_pos(name);
	if (pos == -1)
		throw UnexistingDogException();
	this->dogs.erase(this->dogs.begin() + pos);
	this->write_to_file();
}

void Repo::update_dog(const Dog& d)
{
	int pos = this->find_by_name_pos(d.getName());
	if (pos == -1)
		throw UnexistingDogException();
	this->dogs[pos] = d;
	this->write_to_file();
}

int Repo::find_by_name_pos(const std::string & name)
{
	Dog dog = this->find_by_name(name);
	if (dog.getName() == "")
		return -1;
	int pos = std::find(this->dogs.begin(), this->dogs.end(), dog) - this->dogs.begin();
	return pos;
}

Dog Repo::get_elem_on_pos(int pos)
{
	return this->dogs[pos];
}
