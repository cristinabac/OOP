#include "Dog.h"
#include <Windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <sstream>


Dog::Dog(const std::string& breed, const std::string& name, int age, const std::string& photo)
{
	/*
	Constructor for Dog
	*/
	this->age = age;
	this->breed = breed;
	this->name = name;
	this->photo = photo;
}

//bool Dog::operator=(const Dog& d)

Dog::~Dog()
{
	/*
	Destructor for Dog
	*/
}

bool Dog::operator==(const Dog & d)
{
	if (this->name == d.getName())
		return true;
	return false;
}

void Dog::show()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhoto().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::istream & operator>>(std::istream & is, Dog & d)
{
	std::string s;
	getline(is, s);

	std::vector<std::string> result;
	std::stringstream ss(s);

	std::string token;
	while (getline(ss, token, ','))
		result.push_back(token);

	if (result.size() != 4)
		return is;

	d.breed = result[0];
	d.name = result[1];
	d.age = stoi(result[2]);
	d.photo = result[3];
	return is;
}

std::ostream & operator<<(std::ostream & os, Dog & d)
{
	os << d.getBreed() << "," << d.getName() << "," << d.getAge() << "," << d.getPhoto() << "\n";
	return os;
}
