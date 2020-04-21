#include "LabWork.h"
#include <sstream>


LabWork::~LabWork()
{
}

LabWork::LabWork(Controller& _contr):
	contr{ _contr }
{
	this->initialize();
	this->populate(this->contr.get_repo().get_all_dogs());
}

void LabWork::initialize()
{
	this->setWindowTitle("Filter dogs by breed. Introduce the substring wanted: ");
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	this->dogsList = new QListWidget{};
	this->filter = new QLineEdit{};

	QObject::connect(this->filter, &QLineEdit::textChanged, this, &LabWork::updateMovies);

	mainLayout->addWidget(this->filter);
	mainLayout->addWidget(this->dogsList);


}

void LabWork::populate(std::vector<Dog> filteredList)
{
	for (auto dog : filteredList) {
		std::string row;
		std::stringstream ss;
		ss << dog.getAge();
		row.append(dog.getBreed() + "," + dog.getName() + "," + ss.str() + "," + dog.getPhoto());
		this->dogsList->addItem(row.c_str());
	}

}

void LabWork::updateMovies()
{
	QString filt = this->filter->text();
	//Dog key{};
	//key.setBreed(filt.toStdString());
	std::vector<Dog> newList = this->contr.find_str_in_breed(filt.toStdString());
	this->dogsList->clear();
	this->populate(newList);
}
