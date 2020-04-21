#include "assign1112_oop.h"
#include <QtWidgets/QApplication>
#include "Controller.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include "AdministratorGui.h"
#include "RepoExceptions.h"
#include "UserGui.h"
#include "Bonus.h"

#include "MainGui.h"
#include "LabWork.h"

int main(int argc, char *argv[])
{
	/*
	//iteratia 1 - lab 11
	QApplication a(argc, argv);
	FileAdoptionList* p = nullptr;
	p = new CSVAdoptionList{ "adoptionlist.csv" };

	Repo r{ "dogs.txt" };
	Controller c{ r,p,DogValidator{} };
	AdministratorGui gui{ c };
	gui.show();
	return a.exec();
	delete p;
	*/



	//assign 12
	try {
		QApplication a(argc, argv);
		QMessageBox msgBox;
		msgBox.setText(QT_TR_NOOP("What type of file would you like to store your adoption list?"));
		QAbstractButton* pButtonYes = msgBox.addButton(QT_TR_NOOP("CSV"), QMessageBox::YesRole);
		msgBox.addButton(QT_TR_NOOP("HTML"), QMessageBox::NoRole);
		msgBox.exec();

		FileAdoptionList* p = nullptr;
		if (msgBox.clickedButton() == pButtonYes)
			p = new CSVAdoptionList{ "adoptionlist.csv" };
		else
			p = new HTMLAdoptionList{ "adoptionlist.html" };

		Repo repo{ "dogs.txt" };
		Controller ctrl{ repo, p, DogValidator{} };
		MainGui gui{ ctrl };
		gui.show();

		LabWork l{ ctrl };
		l.show();

		Bonus b{ ctrl };
		b.show();

		return a.exec();
		delete p;

	}
	catch (FileException&)
	{
		QApplication a(argc, argv);
		QMessageBox::critical(0, "Reading data", "Error opening file");
		return a.exec();
	}




	//lab work

	/*
	QApplication a(argc, argv);
	Repo r{ "dogs.txt" };
	FileAdoptionList* p = nullptr;
	p = new CSVAdoptionList{ "adoptionlist.csv" };
	Controller c{ r,p,DogValidator{} };
	LabWork l{ c };
	l.show();
	return a.exec();
	delete p;
	*/
	return 0;
}
