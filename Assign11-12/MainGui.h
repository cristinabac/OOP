#pragma once
#include "C:\Qt\5.12.2\msvc2017_64\include\QtWidgets\qwidget.h"
#include "UserGui.h"
#include "AdministratorGui.h"

class MainGui :
	public QWidget
{
public:
	Controller c;
private:
	QPushButton* administratorButton;
	QPushButton* userButton;
	QWidget* administratorGui;
	QWidget * userGui;

	void initGUI();
	void makeConnections();
	void showAdminGui();
	void showUserGui();

public:
	MainGui(const Controller & _c) :
		c{ _c }
	{
		this->initGUI();
		this->makeConnections();
	}
	~MainGui();
};

