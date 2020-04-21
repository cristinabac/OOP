#pragma once
#include <string>
class Report
{
private:
	std::string description, reporter;
	int latitude, longitude;
	int validated;
public:
	Report();
	~Report();

	Report(std::string d, std::string r, int lat, int lon, int v)
	{
		this->description = d;
		this->reporter = r;
		this->latitude = lat;
		this->longitude = lon;
		this->validated = v;
	};

	std::string getDescription() { return this->description;}
	std::string getReporter() { return this->reporter; }
	int getLatitude() { return this->latitude; }
	int getLongitude() { return this->longitude; }
	int getValidated() { return this->validated; }

	void setValidated(int v) { this->validated = v; }
	void setLatitude(int l) { this->latitude = l; }
	void setLongitude(int l) { this->longitude = l; }
	void setReporter(std::string r) { this->reporter = r; }

	std::string toString() {
		return this->description + " " + this->reporter + " " + std::to_string(this->latitude) + " " + std::to_string(this->longitude) + " " + std::to_string(this->validated);
	}
 
};

