#include "Bonus.h"

#include <QtCharts/QChartGlobal>
#include <QtCharts/qchartview.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieslice.h>
#include <qpieseries.h>
#include <QPieSeries>
#include <QHBoxLayout>
#include <qformlayout.h>
#include <qlineedit.h>
using namespace QtCharts;

void Bonus::initGUI()
{
	this->setWindowTitle("Bonuuuuus :)");
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QPieSeries *series = new QPieSeries();
	std::vector<QPieSlice*> slices;

	std::vector<Dog> dogs = this->c.get_repo().get_all_dogs();
	std::vector<std::string> breeds;
	for (int i = 0; i < dogs.size(); i++)
	{
		std::string actual_breed = dogs[i].getBreed();
		int ok = 1;
		for (int j = 0; j < breeds.size(); j++)
			if (breeds[j] == actual_breed)
				ok = 0;
		if (ok == 1)
			breeds.push_back(actual_breed);
	}
	for (int i = 0; i < breeds.size(); i++)
	{
		int nr = 0;
		for (int j = 0; j < dogs.size(); j++)
			if (dogs[j].getBreed() == breeds[i])
				nr++;
		std::string aux = "";
		aux = aux + breeds[i] + " : " + std::to_string(nr);
		//series->append(breeds[i].c_str(), nr);
		series->append(aux.c_str(), nr);
		slices.push_back(series->slices().at(i));
		slices[i]->setLabelVisible();
	}

	QChart *chart = new QChart();
	chart->setTheme(chart->ChartThemeBlueCerulean);
	chart->addSeries(series);
	chart->setTitle("Dogs statistic by breed");

	QChartView *chart_view = new QChartView(chart);
	chart_view->setRenderHint(QPainter::Antialiasing);
	chart_view->setMinimumWidth(499);

	QVBoxLayout *chart_layout = new QVBoxLayout();
	chart_layout->addWidget(chart_view);

	layout->addLayout(chart_layout);
}

Bonus::~Bonus()
{
}
