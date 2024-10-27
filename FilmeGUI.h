#pragma once

#include "Service.h"
#include "Filme.h"
#include "inchirieri.h"

#include <QWidget>
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include <vector>
#include <qlabel.h>
#include <qtablewidget.h>
using std::vector;
using std::string;

class GUI : public QWidget {
private:
	Service& srv;

	QHBoxLayout* layMain = new QHBoxLayout;
	QListWidget* lst;

	QPushButton* btnAdd;
	QPushButton* btnSterge;
	QPushButton* btnModifica;
	QPushButton* btnFiltreaza;
	QPushButton* btnRaport;
	QPushButton* btnUndo;

	QPushButton* btnAddToRent;

	QPushButton* btnSortCrescTitlu;
	QPushButton* btnSortDescrescTitlu;
	QPushButton* btnSortCrescAnGen;
	QPushButton* btnSortCrescActor;
	QPushButton* btnSortDescrescAnGen;
	QPushButton* btnSortDescrescActor;

	QLineEdit* txtTitlu;
	QLineEdit* txtGen;
	QLineEdit* txtActor;
	QLineEdit* txtAn;

	QVBoxLayout* layBtn = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	QPushButton* btnExit;

	void initGUI();
	void connections();
	void reloadList(const vector<Filme>& filme);
	void addNewFilme();
	void stergeFilme();
	void modificaFilme();
	void undoFilme();
	void resetForm();

public:

	GUI(Service& srv) : srv{ srv } {
		initGUI();
		connections();
		reloadList(srv.getAll());
	}
};