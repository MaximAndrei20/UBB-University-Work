#pragma once
#include <qwidget.h>
#include "Service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include "EventTableModel.h"

class GUI :
    public QWidget
{
	Q_OBJECT
private:
    Service& serv;

    QTableView* allEventsTable;
    EventTableModel* allEventsModel;

    QLineEdit* lineTitle;
    QLineEdit* lineDescription;
    QLineEdit* lineDateTime;
	QLineEdit* lineNumberOfPeople;
    QLineEdit* lineLink;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* filterButton;

    QPushButton* copyButton;
    QListWidget* userEvents;

	QPushButton* removeFromUserButton;
    QPushButton* showButton;
    QPushButton* showCsvButton;
	QPushButton* showHtmlButton;
    QPushButton* undoButton;
	QPushButton* redoButton;

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void undoTriggered();
    void redoTriggered();


public:
    GUI(Service& serv);
    void initGUI();
    void populateList();
    void populateUserList();
    void connectSignalsAndSlots();

    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
	void copyButtonHandler();
	void addShowButtonHandler();
	void showCsvButtonHandler();
	void showHtmlButtonHandler();
	void filterButtonHandler();
	void removeFromUserButtonHandler();

    void undoButtonHandler();
	void redoButtonHandler();

    void onUndo();
	void onRedo();
};

