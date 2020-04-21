#include "UserGui.h"
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>

void UserGui::initGUI()
{
	this->setWindowTitle("User");
	QVBoxLayout * mainLayout = new QVBoxLayout(this);

	QHBoxLayout* filteringLayout = new QHBoxLayout();
	QHBoxLayout * currentLayout = new QHBoxLayout();
	QVBoxLayout* userInteractLayout = new QVBoxLayout();

	QFormLayout* dataLayout = new QFormLayout{};

	this->breedEdit = new QLineEdit{};
	dataLayout->addRow("Breed", this->breedEdit);
	this->ageEdit = new QLineEdit{};
	dataLayout->addRow("Age", this->ageEdit);

	filteringLayout->addLayout(dataLayout);

	this->filterButton = new QPushButton("Filter");
	filteringLayout->addWidget(this->filterButton);

	this->currentDogLabel = new QLabel("Current dog: ");
	this->showCurrentDogLabel = new QLabel("");
	currentLayout->addWidget(this->currentDogLabel);
	currentLayout->addWidget(this->showCurrentDogLabel);

	this->addToAdoptionListButton = new QPushButton("Add to adoption list");
	this->nextButton = new QPushButton("See next dog");
	this->saveToFileButton = new QPushButton("Save to file");
	this->showAdoptionListButton = new QPushButton("Show adoption list");
	userInteractLayout->addWidget(this->addToAdoptionListButton);
	userInteractLayout->addWidget(this->nextButton);
	userInteractLayout->addWidget(this->saveToFileButton);
	userInteractLayout->addWidget(this->showAdoptionListButton);

	mainLayout->addLayout(filteringLayout);
	mainLayout->addLayout(currentLayout);
	mainLayout->addLayout(userInteractLayout);

}

void UserGui::makeConnections()
{
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGui::filterByBreedAndAge);
	QObject::connect(this->addToAdoptionListButton, &QPushButton::clicked, this, &UserGui::addToAdoptionList);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGui::showNext);
	QObject::connect(this->saveToFileButton, &QPushButton::clicked, this, &UserGui::saveToFile);
	QObject::connect(this->showAdoptionListButton, &QPushButton::clicked, this, &UserGui::showAdoptionList);
}

void UserGui::filterByBreedAndAge()
{
	int age = this->ageEdit->text().toInt();
	std::string breed = this->breedEdit->text().toStdString();
	
	this->c.add_dogs_to_adoption_list_by_breed(breed, age);

	if (this->c.get_adoption_list()->is_empty())
	{
		this->showCurrentDogLabel->setText("No such dogs for u! :(");
		return;
	}
	this->c.start_adoption_list();
	Dog d = this->c.get_adoption_list()->get_current_dog();
	std::string current = "\n Breed: " + d.getBreed() + "\n Name: " + d.getName() + "\n Age:" + std::to_string(d.getAge());
	this->showCurrentDogLabel->setText(QString::fromStdString(current));
}

void UserGui::addToAdoptionList()
{
	if (this->c.get_adoption_list()->is_empty())
		return;
	Dog d = this->c.get_adoption_list()->get_current_dog();
	this->c.adopt_dog(d);
	//this->c.get_adoption_list()->sa  save adoption list
	//std::string current = "\n Breed: " + d.getBreed() + "\n Name: " + d.getName() + "\n Age:" + std::to_string(d.getAge());
	//this->showCurrentDogLabel->setText(QString::fromStdString(current));

}

void UserGui::showNext()
{
	if (this->c.get_adoption_list()->is_empty())
		return;
	this->c.next_adoption_list();
	Dog d = this->c.get_adoption_list()->get_current_dog();
	std::string current = "\n Breed: " + d.getBreed() + "\n Name: " + d.getName() + "\n Age:" + std::to_string(d.getAge());
	this->showCurrentDogLabel->setText(QString::fromStdString(current));
}

void UserGui::showAdoptionList()
{
	this->c.get_adoption_list()->display_adoption_list();
}

void UserGui::saveToFile()
{
	this->c.get_adoption_list()->write_to_file();
}

UserGui::~UserGui()
{
}
