#pragma once
#include "Report.h"
#include "Driver.h"
#include <vector>
#include "Subjet.h"
class Repository: public Subjet
{
private:
	std::vector<Report> reports;
	std::vector<Driver> drivers;
	std::string rFile, dFile;
public:
	Repository();
	Repository(std::string r, std::string d)
	{
		this->rFile = r;
		this->dFile = d;
		this->readFromFileDrivers();
		this->readFromFileReports();
		this->notify();
	}
	void readFromFileReports();
	void readFromFileDrivers();
	std::vector<Report> getSortedByDistance(Driver d, int radius);

	std::vector<Report> getReports() { return this->reports; }
	std::vector<Driver> getDrivers() { return this->drivers; }

	std::vector<Report>& getReportsRef() { return this->reports; }
	std::vector<Driver>& getDriversRef() { return this->drivers; }

	int addReport(Report r, Driver d);

	void validateReport(std::string rep);

	void updateDriverLocation(Driver& d, int lat, int lon);

	~Repository();
};

