#pragma once

#include <QMainWindow>
#include "ui_GUI.h"

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;

private slots:
	void on_button1_clicked();
	void on_button2_clicked();
	void on_button3_clicked();
	void on_lineEdit_textChanged(const QString& text);
};

