#include "Repository.h"
#include <fstream>
#include <math.h>



Repository::Repository()
{
}


void Repository::readFromFileReports()
{
	std::ifstream f(this->rFile);
	std::string d, rep;
	int lat, lon, valid;
	while (f >> d >> rep >> lat >> lon >> valid)
	{
		Report r{ d, rep, lat, lon, valid };
		this->reports.push_back(r);
	}
	f.close();
}

void Repository::readFromFileDrivers()
{
	std::ifstream f(this->dFile);
	std::string name, status;
	int lat, lon, score;
	while (f >> name >> status >> lat >> lon >> score)
	{
		Driver d{ name, status, lat, lon, score };
		this->drivers.push_back(d);
	}
	f.close();
}

std::vector<Report> Repository::getSortedByDistance(Driver d, int radius)
{
	std::vector<Report> vct;
	for (auto r : this->reports)
		if (r.getLatitude() > d.getLatitude() - radius && r.getLatitude() < d.getLatitude() + radius && r.getLongitude() > d.getLongitude() - radius && r.getLongitude() < d.getLongitude() + radius)
			vct.push_back(r);
	int i,j;
	for(i=0;i<vct.size()-1;i++)
		for (j = i + 1; j < vct.size(); j++)
		{
			float disti = sqrt((vct[i].getLatitude() - d.getLatitude())*(vct[i].getLatitude() - d.getLatitude()) + (vct[i].getLongitude() - d.getLongitude())*(vct[i].getLongitude() - d.getLongitude()));
			float distj = sqrt((vct[j].getLatitude() - d.getLatitude())*(vct[j].getLatitude() - d.getLatitude()) + (vct[j].getLongitude() - d.getLongitude())*(vct[j].getLongitude() - d.getLongitude()));
			if (disti > distj)
			{
				Report aux = vct[i];
				vct[i] = vct[j];
				vct[j] = aux;
			}
		}
	return vct;
}

int Repository::addReport(Report r, Driver d)
{
	/*
	Input: r - Report
			d - Driver
	Output: returns 1 - in case of success
			returns 0 otherwise
	Driver d adds the report r in the repository only if it is ok
	*/
	if(r.getDescription() == "")
		return 0;
	float dist = sqrt((r.getLatitude() - d.getLatitude())*(r.getLatitude() - d.getLatitude()) + (r.getLongitude() - d.getLongitude())*(r.getLongitude() - d.getLongitude()));
	if (dist > 20)
		return 0;
	this->reports.push_back(r);
	this->notify();
	return 1;
}

void Repository::validateReport(std::string rep)
{
	int pos;
	std::string d;
	for (int i = 0; i < this->reports.size(); i++)
		if (this->reports[i].toString() == rep)
		{
			pos = i;
			d = this->reports[pos].getReporter();
		}
	//Report& r = this->reports[pos];
	//r.setValidated(r.getValidated() + 1);
	int posd;
	for(int i=0;i<this->drivers.size();i++)
		if (this->drivers[i].getName() == d)
		{
			posd = i;
		}
	this->drivers[posd].setScore(this->drivers[posd].getScore() + 1);
	int val = this->reports[pos].getValidated();
	this->reports[pos].setValidated(val + 1);
	this->notify();
}

void Repository::updateDriverLocation(Driver & d, int lat, int lon)
{
	/*
	Input:
			d - reference to Driver
			lat - int
			lon - int
	Output: -
	Changes the position (long and lat) of driver d
	*/
	d.setLatitude(lat);
	d.setLongitude(lon);
	this->notify();
}

Repository::~Repository()
{
}
