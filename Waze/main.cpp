#include "practic_exam.h"
#include <QtWidgets/QApplication>
#include "Repository.h"
#include "DriverWindow.h"
#include <assert.h>


void test()
{
	Repository r{ "reports.txt","drivers.txt" };
	Report rep{ "","Alex",12,12,0 };
	assert(r.addReport(rep, r.getDrivers()[1]) == 0);
	Report rep2{ "","Alex",120,120,0 };
	assert(r.addReport(rep2, r.getDrivers()[1]) == 0);
	Report rep3{ "lala","Alex",12,12,0 };
	assert(r.addReport(rep3, r.getDrivers()[1]) == 1);
}

void test2()
{
	Repository r{ "reports.txt","drivers.txt" };
	assert(r.getDrivers()[0].getLatitude() == 15);
	assert(r.getDrivers()[0].getLongitude() == 15);
	r.updateDriverLocation(r.getDriversRef()[0], 16, 16);
	assert(r.getDrivers()[0].getLatitude() == 16);
	assert(r.getDrivers()[0].getLongitude() == 16);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//practic_exam w;
	//w.show();

	
	Repository r{ "reports.txt","drivers.txt" };
	for (auto &d : r.getDriversRef())
	{
		DriverWindow* w = new DriverWindow{ d,r };
		r.registerObserver(w);
		w->show();
	}
	

	/*
	test();
	test2();
	practic_exam w;
	w.show();*/


	return a.exec();
}
