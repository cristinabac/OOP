#pragma once
#include "Observer.h"
#include <vector>
class Subjet
{
private:
	std::vector<Observer*> obs;
public:
	Subjet();
	void registerObserver(Observer* o)
	{
		this->obs.push_back(o);
	}
	void notify()
	{
		for (auto a : this->obs)
			a->update();
	}

	~Subjet();
};

