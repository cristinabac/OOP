#include "HTMLAdoptionList.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

void HTMLAdoptionList::write_to_file()
{
	std::ofstream f(this->filename);
	f << "<!DOCTYPE html> \n" << "<html> \n";
	f << "<head>\n" << " <title> Shopping List </title> \n" << "</head>\n";
	f << "<body>\n" << "<table border=\"1\" bgcolor=\"#A9D0F5\" align=\"center\">\n";
	f << "<tr>\n <td>Breed</td>\n" << "<td>Name</td>\n" << " <td>Age</td>\n" << "<td>Link to the photo</td>\n </tr>\n ";
	for (auto d : this->user_dogs) {
		f << "<tr>\n"; // tr= table row
		f << "<td>" << d.getBreed() << "</td> \n";
		f << "<td>" << d.getName() << "</td> \n";
		f << "<td>" << d.getAge() << "</td> \n";
		f << "<td> <a href=" << d.getPhoto() << ">Link </a> </td> \n";
		f << "</tr> \n";
	}

	f << "</table>\n" << "</body> \n" << "</html> \n";
	f.close();
}

void HTMLAdoptionList::display_adoption_list()
{
	std::string aux = this->filename;
	ShellExecuteA(NULL, NULL, "chrome.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}
