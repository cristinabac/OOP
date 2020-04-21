#include "AdministratorGui.h"
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>
#include "RepoExceptions.h"
#include "Utils.h"

void AdministratorGui::initGui()
{
	this->setWindowTitle("Administrator");
	QHBoxLayout* layout = new QHBoxLayout{ this };

	this->list = new QListWidget{};

	layout->addWidget(this->list);

	QVBoxLayout* rightSide = new QVBoxLayout{};

	layout->addLayout(rightSide);

	QFormLayout* dataLayout = new QFormLayout{};
	
	this->editBreed = new QLineEdit{};
	dataLayout->addRow("Breed", this->editBreed);
	this->editName = new QLineEdit{};
	dataLayout->addRow("Name", this->editName);
	this->editAge = new QLineEdit{};
	dataLayout->addRow("Age", this->editAge);
	this->editLink = new QLineEdit{};
	dataLayout->addRow("Link", this->editLink);

	rightSide->addLayout(dataLayout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout{};

	this->addButton = new QPushButton("Add");
	this->removeButton = new QPushButton("Remove by selection");
	this->updateButton = new QPushButton("Update");

	buttonsLayout->addWidget(this->addButton);
	buttonsLayout->addWidget(this->removeButton);
	buttonsLayout->addWidget(this->updateButton);

	rightSide->addLayout(buttonsLayout);
}

void AdministratorGui::populateList()
{
	this->list->clear();
	for (auto s : this->c.get_repo().get_all_dogs())
	{
		std::string str = "";
		str += s.getBreed();
		str += ",";
		str += s.getName();
		str += ",";
		str += std::to_string(s.getAge());
		str += ",";
		str += s.getPhoto();
		this->list->addItem(QString::fromStdString(str));
	}
}

void AdministratorGui::makeConnections()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdministratorGui::addDog);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdministratorGui::removeDog);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdministratorGui::updateDog);
}

void AdministratorGui::addDog()
{
	std::string name = this->editName->text().toStdString();
	std::string breed = this->editBreed->text().toStdString();
	int age = this->editAge->text().toInt();
	std::string link = this->editLink->text().toStdString();
	try
	{
		this->c.add_dog_controller(breed, name, age, link);
		this->populateList();
	}
	catch (DogException& e)
	{
		std::string err = "";
		for (auto s : e.getErrors())
			err += s;
		this->messageBox->critical(0, "error adding dog", QString::fromStdString(err));
	}
	catch (RepoException& e)
	{
		std::string err = e.what();
		this->messageBox->critical(0, "error adding dog", QString::fromStdString(err));
	}
	catch (FileException& e)
	{
		std::string err = e.what();
		this->messageBox->critical(0, "error adding dog", QString::fromStdString(err));
	}
}

void AdministratorGui::updateDog()
{
	std::string name = this->editName->text().toStdString();
	std::string breed = this->editBreed->text().toStdString();
	int age = this->editAge->text().toInt();
	std::string link = this->editLink->text().toStdString();
	try
	{
		this->c.update_dog_controller(breed, name, age, link);
		this->populateList();
	}
	catch (DogException& e)
	{
		std::string err = "";
		for (auto s : e.getErrors())
			err += s;
		this->messageBox->critical(0, "error updating dog", QString::fromStdString(err));
	}
	catch (RepoException& e)
	{
		std::string err = e.what();
		this->messageBox->critical(0, "error updating dog", QString::fromStdString(err));
	}
	catch (FileException& e)
	{
		std::string err = e.what();
		this->messageBox->critical(0, "error updating dog", QString::fromStdString(err));
	}
}

void AdministratorGui::removeDog()
{
	QList<QListWidgetItem*> selectedList = this->list->selectedItems();
	foreach(QListWidgetItem * item, selectedList)
	{
		std::string line = (item->text()).toStdString();
		std::vector<std::string> tokens = tokenize(line, ',');

		std::string name = tokens[1];
		//this->messageBox->critical(0, "error removing dog", QString::fromStdString(name));
		this->c.remove_dog_controller(name);
		delete this->list->takeItem(this->list->row(item));

	}
}

AdministratorGui::~AdministratorGui()
{
}
