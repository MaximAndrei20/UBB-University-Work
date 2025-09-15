#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Event.h"

class EventTableModel : public QAbstractTableModel
{
    Q_OBJECT
        std::vector<Event> events;
public:
    EventTableModel(const std::vector<Event>& events, QObject* parent = nullptr)
        : QAbstractTableModel(parent), events(events) {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return static_cast<int>(events.size());
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 5; // title, description, dateTime, numberOfPeople, link
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();
        const Event& e = events[index.row()];
        switch (index.column()) {
        case 0: return QString::fromStdString(e.getTitle());
        case 1: return QString::fromStdString(e.getDescription());
        case 2: return QString::fromStdString(e.getDateTime());
        case 3: return e.getNumberOfPeople();
        case 4: return QString::fromStdString(e.getLink());
        default: return QVariant();
        }
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole)
            return QVariant();
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Title";
            case 1: return "Description";
            case 2: return "DateTime";
            case 3: return "Number of People";
            case 4: return "Link";
            default: return QVariant();
            }
        }
        return QVariant();
    }
	const Event& getEventAt(int row) const {
		if (row < 0 || row >= events.size()) {
			throw std::out_of_range("Row index out of range");
		}
		return events[row];
	}
};