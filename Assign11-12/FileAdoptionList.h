#pragma once
#include <string>
#include "AdoptionList.h"

class FileAdoptionList : public AdoptionList
{
protected:
	std::string filename;
public:
	FileAdoptionList(const std::string & filename);
	virtual ~FileAdoptionList();
	virtual void write_to_file() = 0;
	virtual void display_adoption_list() = 0;
};

