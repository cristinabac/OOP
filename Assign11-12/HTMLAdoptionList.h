#pragma once
#include "FileAdoptionList.h"
#include <vector>

class HTMLAdoptionList : public FileAdoptionList
{
public:
	HTMLAdoptionList(const std::string & filename) : FileAdoptionList{ filename } {};
	void write_to_file() override;
	void display_adoption_list() override;
};

