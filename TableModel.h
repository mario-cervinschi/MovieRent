#pragma once

#include "Filme.h"
#include <vector>
#include <qdebug.h>
#include <QAbstractTableModel>

using std::vector;

class TableModel: public QAbstractTableModel
{
private:
	vector<Filme> elems;

public:
	TableModel(const vector<Filme>& filme) : elems{ filme } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return elems.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::DisplayRole) {
			Filme f = elems[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(f.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(f.getActor());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(f.getGen());
			}
			else if (index.column() == 3) {
				return QString::number(f.getAn());
			}
		}

		return QVariant{};
	}

	void setOferte(const vector<Filme>& filme) {
		beginResetModel();
		this->elems = filme;
		endResetModel();
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	QStringList getFormattedList() const {
		QStringList list;
		for (const auto& f : elems) {
			QString formatted = QString::fromStdString(f.getTitlu()) + " | " + QString::fromStdString(f.getActor()) + " | " + QString::fromStdString(f.getGen()) + " | " + QString::number(f.getAn());
			list.append(formatted);
		}
		return list;
	}

};

