#include "DogValidator.h"



DogValidator::DogValidator()
{
}

void DogValidator::validate(const Dog & d)
{
	std::vector<std::string> errors;
	if (d.getName().size() < 3)
		errors.push_back("\n Invalid name! \n");
	if (d.getBreed().size() < 3)
		errors.push_back("\n Invalid breed! \n");
	if (d.getAge() < 1)
		errors.push_back("\n The age must be > 0! \n");

	if (errors.size() > 0)
		throw DogException(errors);
}


DogException::DogException(std::vector<std::string> err) :
	errors{ err }
{
}
