#include "DriverWindow.h"
#include <qmessagebox.h>

DriverWindow::DriverWindow(Driver& d, Repository& r, QWidget *parent)
	: QWidget(parent), driver{ d }, repo{ r }
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromStdString(driver.getName() + " " + driver.getStatus() + " " + std::to_string(driver.getLatitude()) + " " + std::to_string(driver.getLongitude()) + " " +std::to_string(driver.getScore())));
	this->ui.radiusSpinBox->setValue(10);
	//this->update();
	this->populate();
	if (this->driver.getStatus() == "baby")
		this->setStyleSheet("background-color: green");
	if (this->driver.getStatus() == "regular")
		this->setStyleSheet("background-color: yellow");
	if (this->driver.getStatus() == "advanced")
		this->setStyleSheet("background-color: red");
	

	QObject::connect(this->ui.radiusSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &DriverWindow::radiusChanged);
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &DriverWindow::addReport);
	QObject::connect(this->ui.validateButton, &QPushButton::clicked, this, &DriverWindow::validate);
	QObject::connect(this->ui.NpushButton, &QPushButton::clicked, this, &DriverWindow::moveN);
	QObject::connect(this->ui.SpushButton_2, &QPushButton::clicked, this, &DriverWindow::moveS);
	QObject::connect(this->ui.EpushButton_3, &QPushButton::clicked, this, &DriverWindow::moveE);
	QObject::connect(this->ui.VpushButton_4, &QPushButton::clicked, this, &DriverWindow::moveV);
}

DriverWindow::~DriverWindow()
{
}

void DriverWindow::update()
{
	this->populate();
	this->setWindowTitle(QString::fromStdString(driver.getName() + " " + driver.getStatus() + " " + std::to_string(driver.getLatitude()) + " " + std::to_string(driver.getLongitude()) + " " + std::to_string(driver.getScore())));
	if (this->driver.getScore() == 10 && this->driver.getStatus() == "regular")
	{
		QMessageBox* m = new QMessageBox{};
		m->setWindowTitle(QString::fromStdString(this->driver.getName()));
		m->setText("Congrats! you are now advanced! :)");
		m->show();
		this->driver.setStatus("adavanced");
		this->driver.setScore(15);
		this->setStyleSheet("background-color: red");
		this->setWindowTitle(QString::fromStdString(driver.getName() + " " + driver.getStatus() + " " + std::to_string(driver.getLatitude()) + " " + std::to_string(driver.getLongitude()) + " " + std::to_string(driver.getScore())));

	}
}

void DriverWindow::populate()
{
	/*
	this->ui.reportsList->clear();
	for (auto a : this->repo.getReports())
		this->ui.reportsList->addItem(QString::fromStdString(a.toString()));
	*/
	this->ui.reportsList->clear();
	std::vector<Report> vct = this->repo.getSortedByDistance(this->driver,  this->ui.radiusSpinBox->value());
	for (auto a : vct)
		this->ui.reportsList->addItem(QString::fromStdString(a.toString()));
	if (this->driver.getStatus() == "baby")
		this->setStyleSheet("background-color: green");
	if (this->driver.getStatus() == "regular")
		this->setStyleSheet("background-color: yellow");
	if (this->driver.getStatus() == "advanced")
		this->setStyleSheet("background-color: red");

}

void DriverWindow::radiusChanged()
{
	this->populate();
}

void DriverWindow::addReport()
{
	std::string descr = this->ui.descriptionEdit->text().toStdString();
	int lat = this->ui.latitudeEdit->text().toInt();
	int lon = this->ui.longitudineEdit->text().toInt();
	Report r{ descr, this->driver.getName(), lat, lon, 0 };
	int res = this->repo.addReport(r, this->driver);
	if (res == 0)
	{
		QMessageBox* m = new QMessageBox{};
		m->setText("Empty string or distance > 20 !! :(");
		m->show();
	}
}

void DriverWindow::validate()
{
	std::string str = this->ui.reportsList->currentItem()->text().toStdString();
	int ok = 1;
	for (int i = 0; i < this->repo.getReports().size(); i++)
		if (this->repo.getReports()[i].toString() == str)
			if (this->repo.getReports()[i].getReporter() == this->driver.getName())
				ok = 0;
	for (int i = 0; i < this->repo.getReports().size(); i++)
		if (this->repo.getReports()[i].toString() == str)
			if (this->repo.getReports()[i].getValidated() == 2)
				ok = 0;
	if (ok == 0)
	{
		QMessageBox* m = new QMessageBox{};
		m->setText("You cannot validate your own report! Or it is already 2 times  validated :(");
		m->show();
	}
	else
		this->repo.validateReport(str);

}

void DriverWindow::moveN()
{
	int lat = this->driver.getLatitude();
	int lon = this->driver.getLongitude()+1;
	this->repo.updateDriverLocation(this->driver, lat, lon);
}

void DriverWindow::moveS()
{
	int lat = this->driver.getLatitude();
	int lon = this->driver.getLongitude() - 1;
	this->repo.updateDriverLocation(this->driver, lat, lon);
}

void DriverWindow::moveE()
{
	int lat = this->driver.getLatitude() + 1;
	int lon = this->driver.getLongitude();
	this->repo.updateDriverLocation(this->driver, lat, lon);
}

void DriverWindow::moveV()
{
	int lat = this->driver.getLatitude() - 1;
	int lon = this->driver.getLongitude();
	this->repo.updateDriverLocation(this->driver, lat, lon);
}
