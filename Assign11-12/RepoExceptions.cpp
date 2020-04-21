#include "RepoExceptions.h"



FileException::FileException(const std::string & msg) :
	message(msg)
{
}

const char * FileException::what()
{
	return this->message.c_str();
}

RepoException::RepoException() :
	exception{}, message{ "" }
{
}

RepoException::RepoException(const std::string & msg) :
	message(msg)
{
}

const char * RepoException::what()
{
	return this->message.c_str();
}

const char * UnexistingDogException::what()
{
	return "\n There is no dog with that name \n";
}

const char * ExistingNameException::what()
{
	return "\n There is another dog with that name \n";
}
