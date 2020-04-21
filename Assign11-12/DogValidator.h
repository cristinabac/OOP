#pragma once
#include <vector>
#include <string>
#include "Dog.h"

class DogException
{
private:
	std::vector<std::string> errors;
public:
	DogException(std::vector<std::string> err);
	std::vector<std::string> getErrors() const { return this->errors; }
};

class DogValidator
{
public:
	DogValidator();
	void validate(const Dog& d);
};

