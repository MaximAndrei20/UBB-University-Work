#pragma once

#include <QAbstractTableModel>

class QtClass  : public QAbstractTableModel
{
	Q_OBJECT

public:
	QtClass(QObject *parent);
	~QtClass();
};

