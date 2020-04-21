#pragma once
#include <string>
#include "FileAdoptionList.h"

class CSVAdoptionList : public FileAdoptionList
{
public:
	CSVAdoptionList(const std::string & filename) : FileAdoptionList{ filename } {};
	void write_to_file() override;
	void display_adoption_list() override;
};

