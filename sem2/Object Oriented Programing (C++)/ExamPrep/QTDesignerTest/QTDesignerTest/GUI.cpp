#include "GUI.h"
#include <QMessageBox>

GUI::GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

GUI::~GUI()
{}

void GUI::on_button1_clicked()
{
	ui.lineEdit->setText("Button 1 clicked");
}
void GUI::on_button2_clicked()
{
	ui.lineEdit->setText("Button 2 clicked");
}
void GUI::on_button3_clicked()
{
	ui.lineEdit->setText("Button 3 clicked");
}

void GUI::on_lineEdit_textChanged(const QString& text)
{
	// 
}
