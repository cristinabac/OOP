#pragma once
#include <string>

class Driver
{
private:
	std::string name, status;
	int latitude, longitude, score;
public:
	Driver();
	Driver(std::string n, std::string s, int lat, int lon, int score)
	{
		this->name = n;
		this->status = s;
		this->latitude = lat;
		this->longitude = lon;
		this->score = score;
	};

	std::string getName() { return this->name; }
	std::string getStatus() { return this->status; }
	int getLatitude() { return this->latitude; }
	int getLongitude() { return this->longitude; }
	int getScore() { return this->score; }

	void setScore(int s) { this->score = s; }
	void setLatitude(int l) { this->latitude = l; }
	void setLongitude(int l) { this->longitude = l; }
	void setStatus(std::string s) { this->status = s; }


	~Driver();
};

