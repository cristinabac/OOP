#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_assign1112_oop.h"

class assign1112_oop : public QMainWindow
{
	Q_OBJECT

public:
	assign1112_oop(QWidget *parent = Q_NULLPTR);

private:
	Ui::assign1112_oopClass ui;
};
