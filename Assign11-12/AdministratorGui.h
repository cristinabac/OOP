#pragma once
#include "C:\Qt\5.12.2\msvc2017_64\include\QtWidgets\qwidget.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "Controller.h"


class AdministratorGui :
	public QWidget
{
private:
	Controller c;

	QListWidget* list;
	QLineEdit* editName;
	QLineEdit* editBreed;
	QLineEdit* editAge;
	QLineEdit* editLink;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QMessageBox* messageBox;

	void initGui();
	void populateList();
	void addDog();
	void removeDog();
	void updateDog();
	void makeConnections();

public:
	AdministratorGui(Controller& ctrl) : c{ ctrl }
	{
		this->initGui();
		this->makeConnections();
		this->populateList();
	}
	~AdministratorGui();
};

