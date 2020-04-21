#pragma once
#include "C:\Qt\5.12.2\msvc2017_64\include\QtWidgets\qwidget.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include "Controller.h"

class UserGui :
	public QWidget
{

private:
	//QLabel * filterLabel;
	QLabel * currentDogLabel;
	QLabel * showCurrentDogLabel;
	QLineEdit* breedEdit;
	QLineEdit* ageEdit;
	QPushButton * filterButton;
	QPushButton * addToAdoptionListButton;
	QPushButton * nextButton;
	QPushButton * saveToFileButton;
	QPushButton* showAdoptionListButton;

	Controller c;

	void initGUI();
	void makeConnections();
	void filterByBreedAndAge();
	void addToAdoptionList();
	void showNext();
	void showAdoptionList();
	void saveToFile();

public:
	UserGui(const Controller& _c) :
		c{ _c }
	{
		this->initGUI();
		this->makeConnections();
	}
	~UserGui();
};

