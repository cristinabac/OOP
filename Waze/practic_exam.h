#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practic_exam.h"

class practic_exam : public QMainWindow
{
	Q_OBJECT

public:
	practic_exam(QWidget *parent = Q_NULLPTR);

private:
	Ui::practic_examClass ui;
};
