#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;
public:
	FileException(const std::string & msg);
	virtual const char* what();
};


class RepoException : public std::exception
{
protected:
	std::string message;
public:
	RepoException();
	RepoException(const std::string &msg);
	virtual ~RepoException() {}
	virtual const char* what();
};


class UnexistingDogException : public RepoException
{
	const char* what();
};

class ExistingNameException : public RepoException
{
	const char* what();
};

