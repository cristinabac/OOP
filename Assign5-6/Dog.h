#pragma once
#include <iostream>


class Dog
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photo;

public:
	Dog(const std::string& breed="", const std::string& name="", int age=0, const std::string& photo="");
	~Dog();

	int getAge() const { return age; }
	std::string getBreed() const { return breed; }
	std::string getName() const { return name; }
	std::string getPhoto() const { return photo; }

	friend std::istream& operator>>(std::istream& is, Dog& d);
	friend std::ostream& operator<<(std::ostream& os, Dog& d);

	bool operator==(const Dog& d);
	void show();


};

