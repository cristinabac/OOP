#include "CSVAdoptionList.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

void CSVAdoptionList::write_to_file()
{
	std::ofstream f(this->filename);
	for (auto d : this->user_dogs)
		f << d;
	f.close();
}

void CSVAdoptionList::display_adoption_list()
{
	std::string aux = this->filename;
	ShellExecuteA(NULL, NULL, "notepad.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}
