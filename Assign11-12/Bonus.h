#pragma once
#include "C:\Qt\5.12.2\msvc2017_64\include\QtWidgets\qwidget.h"
#include "Controller.h"
class Bonus :
	public QWidget
{
private:
	Controller c;
	void initGUI();
public:
	Bonus(Controller& _c) :
		c{ _c }
	{
		this->initGUI();
	}
	~Bonus();
};

