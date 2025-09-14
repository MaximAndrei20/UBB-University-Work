#include "GUI.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service(service)
{
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
	QHBoxLayout* mainWindow = new QHBoxLayout(this);

	allEquations = new QListWidget();

	QFormLayout* equationInputs = new QFormLayout();
	aInput = new QLineEdit();
	bInput = new QLineEdit();
	cInput = new QLineEdit();

	QVBoxLayout* buttonsLabels = new QVBoxLayout();

	equationInputs->addRow("a:", aInput);
	equationInputs->addRow("b:", bInput);
	equationInputs->addRow("c:", cInput);

	mainWindow->addWidget(allEquations);
	buttonsLabels->addLayout(equationInputs);

	modifyButton = new QPushButton("Modify");
	showSolutionButton = new QPushButton("Show Solution");
	buttonsLabels->addWidget(modifyButton);
	buttonsLabels->addWidget(showSolutionButton);
	mainWindow->addLayout(buttonsLabels);
	// adding widgets
}

void GUI::populateList()
{
	if (allEquations->count() > 0)
		allEquations->clear();
	std::vector<Equation> equations = service.getEquations();
	for (const auto& eq : equations) {
		QString itemText;
		std::string str = eq.toString();
		if (str.empty())
			itemText = "0*x^2, 0, 0"; // Default case if no equation is present
		else
			itemText = QString::fromStdString(str);
		allEquations->addItem(itemText);
	}
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(modifyButton, &QPushButton::clicked, this, &GUI::modifyButtonHandler);
	QObject::connect(showSolutionButton, &QPushButton::clicked, this, &GUI::showSolutionButtonHandler);
}

void GUI::modifyButtonHandler()
{
	// get the input from the line edits and pass it to the service
	QString aText = aInput->text();
	QString bText = bInput->text();
	QString cText = cInput->text();
	std::string aStr = aText.toStdString(),
		bStr = bText.toStdString(),
		cStr = cText.toStdString();
	double a = aStr.empty() ? -999 : std::stod(aStr);
	double b = bStr.empty() ? -999 : std::stod(bStr);
	double c = cStr.empty() ? -999 : std::stod(cStr);

	//get the selected item
	int selectedIndex = allEquations->currentRow();
	QListWidgetItem* selectedItem = allEquations->currentItem();
	if (!selectedItem) {
		QMessageBox::warning(this, "Warning", "Please select an equation to modify.");
		return;
	}

	if (selectedIndex < 0 || selectedIndex >= service.getEquations().size()) {
		QMessageBox::warning(this, "Warning", "Please select an equation to modify.");
		return;
	}
	service.modify(selectedIndex, a, b, c);
	this->populateList(); // Refresh the list after modification
}

void GUI::showSolutionButtonHandler()
{
	if (allEquations->count() == 0) {
		QMessageBox::warning(this, "Warning", "No equations available to show solutions.");
		return;
	}
	int selecetedIndex = allEquations->currentRow();
	if (selecetedIndex < 0 || selecetedIndex >= service.getEquations().size()) {
		QMessageBox::warning(this, "Warning", "Please select an equation to show solutions.");
		return;
	}
	std::pair<std::pair<double, double>, std::pair<double, double>> solutions = service.getEquations()[selecetedIndex].computeSolutions();
	
	QString message = QString("Solutions:\n"
		"X1: %1 + %2i\n"
		"X2: %3 + %4i")
		.arg(solutions.first.first)
		.arg(solutions.first.second)
		.arg(solutions.second.first)
		.arg(solutions.second.second);
	QMessageBox::information(this, "Solutions", message);
}
