#pragma once
#include <QDialog>
#include <QTableView>
#include "EventTableModel.h"
#include <QVBoxLayout>

class EventsTableViewDialog : public QDialog
{
    Q_OBJECT
public:
    EventsTableViewDialog(const std::vector<Event>& events, QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Events Table");
        resize(800, 400);
        QTableView* tableView = new QTableView(this);
        EventTableModel* model = new EventTableModel(events, this);
        tableView->setModel(model);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(tableView);
        setLayout(layout);
    }
};