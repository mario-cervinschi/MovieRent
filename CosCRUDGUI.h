#pragma once

#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "inchirieri.h"
#include "observer.h"
#include <qdialog.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "TableModel.h"
#include <qstringlistmodel.h>

using std::vector;

class CosGUILista : public QWidget, public Observer {
private:
	Service& srv;
	inchirieri& rent;
	QHBoxLayout* rentLayMain = new QHBoxLayout;
	
	QTableWidget* rentTable;

	TableModel* modelTabel;
	QListView* lst = new QListView;
	
	QLineEdit* txtFisier;
	QLineEdit* txtRandom;
	QPushButton* btnEmptyRent;
	QPushButton* btnRandomRent;
	QPushButton* btnExportRent;

	void reloadList(const vector<Filme>& filme) {
		modelTabel->setOferte(filme);
		QStringList formattedList = modelTabel->getFormattedList();
		QStringListModel* listModel = new QStringListModel(this);
		listModel->setStringList(formattedList);
		lst->setModel(listModel);
	}

	void init() {
		setLayout(rentLayMain);
		QWidget* wid1 = new QWidget;
		
		QVBoxLayout* vlTable = new QVBoxLayout;
		wid1->setLayout(vlTable);
		
		vlTable->addWidget(lst);
				
		//rentTable = new QTableWidget(this);
		
		//vlTable->addWidget(rentTable);
		
		//rentTable->setRowCount(0);
		//rentTable->setColumnCount(4);
			
		
		
		QHBoxLayout* hlBtns1 = new QHBoxLayout;
		QHBoxLayout* hlBtns2 = new QHBoxLayout;
		
		btnEmptyRent = new QPushButton("Goleste lista");
		btnRandomRent = new QPushButton("Adauga random");
		hlBtns1->addWidget(btnRandomRent);
		hlBtns1->addWidget(btnEmptyRent);
		vlTable->addLayout(hlBtns1);
		
		btnExportRent = new QPushButton("Export");
		hlBtns2->addWidget(btnExportRent);
		vlTable->addLayout(hlBtns2);
		
		rentLayMain->addWidget(wid1);
	}

	void connections() {
		rent.addObserver(this);
		
		QObject::connect(btnEmptyRent, &QPushButton::clicked, [&]() {
			rent.empty_rent_nonobs();
			reloadList(rent.get_all());
			});
	
		QObject::connect(btnRandomRent, &QPushButton::clicked, [&]() {
			
			QDialog* dialog = new QDialog;
			dialog->setWindowTitle("Random options");
			auto randomButton = new QPushButton("Adauga atatea filme");
	
			auto layoutTotal = new QVBoxLayout(dialog);
	
			QFormLayout* formText = new QFormLayout;
			QWidget* widForm = new QWidget;
	
			widForm->setLayout(formText);
			txtRandom = new QLineEdit;
			formText->addRow(new QLabel("Nr. filme random: "), txtRandom);
	
			layoutTotal->addWidget(widForm);
	
			auto layout = new QHBoxLayout;
			layout->addWidget(randomButton);
	
			layoutTotal->addLayout(layout);
	
			QObject::connect(randomButton, &QPushButton::clicked, [&]() {
				auto nr = txtRandom->text().toInt();
				if (nr > 0) {
					rent.random_add(srv.getAll(), nr);
					dialog->close();
				}
				else {
					QMessageBox::critical(this, "Invalid", "Nr. random nu poate fi negativ/text.");
				}
	
				});
	
			dialog->exec();
			reloadList(rent.get_all());
			});
	
		QObject::connect(btnExportRent, &QPushButton::clicked, [&]() {
			QDialog* dialog = new QDialog;
			dialog->setWindowTitle("Export options");
	
			auto cvsButton = new QPushButton("CSV");
			auto htmlButton = new QPushButton("HTML");
			
			auto layoutTotal = new QVBoxLayout(dialog);
	
			QFormLayout* formText = new QFormLayout;
			QWidget* widForm = new QWidget;
			widForm->setLayout(formText);
			txtFisier = new QLineEdit;
			formText->addRow(new QLabel("Nume fisier: "), txtFisier);
			
			layoutTotal->addWidget(widForm);
	
			auto layout = new QHBoxLayout;
			layout->addWidget(cvsButton);
			layout->addWidget(htmlButton);
	
			layoutTotal->addLayout(layout);
	
			QObject::connect(cvsButton, &QPushButton::clicked, [&]() {
				auto text = txtFisier->text().toStdString();
				if (text.size() != 0) {
					rent.save_to_file(text + ".csv");
					dialog->close();
				}
				else {
					QMessageBox::critical(this, "Invalid", "Numele fisier nu poate fi gol.");
				}
				
				});
	
			QObject::connect(htmlButton, &QPushButton::clicked, [&]() {
				auto text = txtFisier->text().toStdString();
				if (text.size() != 0) {
					rent.save_to_file(text + ".html");
					dialog->close();
				}
				else {
					QMessageBox::critical(this, "Invalid", "Numele fisier nu poate fi gol.");
				}
	
				});
	
			dialog->exec();
			});
	}

public:

	CosGUILista(inchirieri& _rent, Service& _srv) : rent{ _rent }, srv{ _srv } {
		init();
			modelTabel = new TableModel{ rent.get_all() };
		lst->setModel(modelTabel);
		connections();
		reloadList(rent.get_all());
	}

	void update() override {
		reloadList(rent.get_all());
	}

	~CosGUILista() {
		rent.removeObserver(this);
	}

};