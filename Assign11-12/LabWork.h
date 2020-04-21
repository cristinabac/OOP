#pragma once

#include <QWidget>
#include "Controller.h"
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qlineedit.h>


class LabWork : public QWidget
{

private:
	Controller contr;
	QListWidget* dogsList;
	QLineEdit* filter;
public:
	//LabWork();
	~LabWork();

	LabWork(Controller& _contr);

	void initialize();

	void populate(std::vector<Dog> filteredList);

private slots:
	void updateMovies();

};
