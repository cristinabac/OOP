#include "MainGui.h"
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>

void MainGui::initGUI()
{
	this->setWindowTitle("Chose mode: ");

	QVBoxLayout * mainLayout = new QVBoxLayout(this);
	QVBoxLayout * buttonsLayout = new QVBoxLayout();

	this->administratorButton = new QPushButton("Administrator");
	this->userButton = new QPushButton("User");
	buttonsLayout->addWidget(this->administratorButton);
	buttonsLayout->addWidget(this->userButton);

	this->userButton->setText(QString::fromStdString("User"));	this->setStyleSheet("* {color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));""background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 lightsteelblue, stop:1 grey);}");

	mainLayout->addLayout(buttonsLayout);
}

void MainGui::makeConnections()
{
	QObject::connect(this->administratorButton, &QPushButton::clicked, this, &MainGui::showAdminGui);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &MainGui::showUserGui);
}

void MainGui::showAdminGui()
{
	this->administratorGui = new AdministratorGui{ this->c };
	this->administratorGui->show();
}

void MainGui::showUserGui()
{
	this->userGui = new UserGui{ this->c };
	this->userGui->show();
}

MainGui::~MainGui()
{
}
