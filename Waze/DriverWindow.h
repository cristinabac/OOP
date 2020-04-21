#pragma once

#include <QWidget>
#include "ui_DriverWindow.h"
#include "Repository.h"
#include "Observer.h"

class DriverWindow : public QWidget, public Observer
{
	Q_OBJECT

private:
	Driver& driver;
	Repository& repo;
public:
	DriverWindow(Driver& d, Repository& r,QWidget *parent = Q_NULLPTR);
	~DriverWindow();
	void update() override;
	void populate();
	void radiusChanged();
	void addReport();
	void validate();
	void moveN();
	void moveS();
	void moveE();
	void moveV();

private:
	Ui::DriverWindow ui;
};
