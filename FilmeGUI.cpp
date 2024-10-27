#include "FilmeGUI.h"
#include "validator.h"
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qtimer.h>
#include <qdialog.h>

//initializare GUI
//creare interfata grafica frumoasa
void GUI::initGUI() {

	setLayout(layMain);

	//widget partea stanga
	//cu lista filmelor
	//si sortari
	QWidget* wid = new QWidget;
	QVBoxLayout* vlLista = new QVBoxLayout;
	wid->setLayout(vlLista);
	lst = new QListWidget;
	vlLista->addWidget(lst);

	QVBoxLayout* vlBtnsFilme = new QVBoxLayout;
	QWidget* widBtnFilme = new QWidget;

	QHBoxLayout* lyBtnsFilme1 = new QHBoxLayout;
	QHBoxLayout* lyBtnsFilme2 = new QHBoxLayout;
	QHBoxLayout* lyBtnsFilme3 = new QHBoxLayout;
	QHBoxLayout* lyBtnsFilme4 = new QHBoxLayout;

	auto labelSortari = new QLabel("Sortari dupa:");
	widBtnFilme->setLayout(vlBtnsFilme);
	vlBtnsFilme->addWidget(labelSortari);

	auto labelTitlu = new QLabel("TITLU: ");
	lyBtnsFilme1->addWidget(labelTitlu);
	btnSortCrescTitlu = new QPushButton("crescator");
	lyBtnsFilme1->addWidget(btnSortCrescTitlu);

	btnSortDescrescTitlu = new QPushButton("descrescator");
	lyBtnsFilme1->addWidget(btnSortDescrescTitlu);

	vlBtnsFilme->addLayout(lyBtnsFilme1);
	 
	auto labelAnGen = new QLabel("AN/GEN: ");
	lyBtnsFilme2->addWidget(labelAnGen);
	btnSortCrescAnGen = new QPushButton("crescator");
	lyBtnsFilme2->addWidget(btnSortCrescAnGen);

	btnSortDescrescAnGen = new QPushButton("descrescator");
	lyBtnsFilme2->addWidget(btnSortDescrescAnGen);

	vlBtnsFilme->addLayout(lyBtnsFilme2);

	auto labelActor = new QLabel("ACTOR: ");
	lyBtnsFilme4->addWidget(labelActor);
	btnSortCrescActor = new QPushButton("crescator");
	lyBtnsFilme4->addWidget(btnSortCrescActor);

	btnSortDescrescActor = new QPushButton("descrescator");
	lyBtnsFilme4->addWidget(btnSortDescrescActor);

	vlBtnsFilme->addLayout(lyBtnsFilme4);

	btnAddToRent = new QPushButton("Adauga la rent");
	lyBtnsFilme3->addWidget(btnAddToRent);
	btnAddToRent->setDisabled(true);

	vlBtnsFilme->addLayout(lyBtnsFilme3);

	vlLista->addWidget(widBtnFilme);

	layMain->addWidget(wid);

	//widget partea dreapta cu form
	//si butoanele aferente de
	//adauga, sterge, etc;
	QWidget* widDate = new QWidget;
	QFormLayout* formDate = new QFormLayout;
	widDate->setLayout(formDate);
	txtTitlu = new QLineEdit;
	formDate->addRow(new QLabel("Titlu: "), txtTitlu);
	txtGen = new QLineEdit;
	formDate->addRow(new QLabel("Gen: "), txtGen);
	txtActor = new QLineEdit;
	formDate->addRow(new QLabel("Actor: "), txtActor);
	txtAn = new QLineEdit;
	formDate->addRow(new QLabel("An: "), txtAn);

	QHBoxLayout* hlUsualButtons = new QHBoxLayout;
	QHBoxLayout* hlShowButtons = new QHBoxLayout;

	btnAdd = new QPushButton("Adauga film");
	btnModifica = new QPushButton("Modifica film");
	btnSterge = new QPushButton("Sterge film");
	btnUndo = new QPushButton("Undo");
	btnFiltreaza = new QPushButton("Filter");
	btnRaport = new QPushButton("Raport");

	hlUsualButtons->addWidget(btnAdd);
	hlUsualButtons->addWidget(btnModifica);
	hlUsualButtons->addWidget(btnSterge);

	hlShowButtons->addWidget(btnFiltreaza);
	hlShowButtons->addWidget(btnRaport);
	
	formDate->addRow(hlUsualButtons);
	formDate->addRow(hlShowButtons);
	formDate->addRow(btnUndo);

	layMain->addWidget(widDate);

	btnDyn->setLayout(layBtn);
	layMain->addWidget(btnDyn);
}

//conexiunile dintre butoane/campuri si cod
void GUI::connections() {
	

	QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::addNewFilme);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &GUI::stergeFilme);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &GUI::modificaFilme);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &GUI::undoFilme);

	//conexiune pt sortare descresc titlu
	QObject::connect(btnSortDescrescTitlu, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordTitlu, true);
		reloadList(srv.getAll());
		});

	//conexiune pt sortare cresc titlu
	QObject::connect(btnSortCrescTitlu, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordTitlu);
		reloadList(srv.getAll());
		});

	//conexiune pt sortare cresc an/gen
	QObject::connect(btnSortCrescAnGen, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordAnGen);
		reloadList(srv.getAll());
		});

	//conexiune pt sortare descresc an/gen
	QObject::connect(btnSortDescrescAnGen, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordAnGen, true);
		reloadList(srv.getAll());
		});
	
	//conexiune pt sortare cresc actor
	QObject::connect(btnSortCrescActor, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordActor);
		reloadList(srv.getAll());
		});

	//conexiune pt sortare descresc actor
	QObject::connect(btnSortDescrescActor, &QPushButton::clicked, [&]() {
		srv.sort(srv.ordActor, true);
		reloadList(srv.getAll());
		});

	//conexiune pt buton filtrare
	QObject::connect(btnFiltreaza, &QPushButton::clicked, [&]() {
		//cream un pop-up window in care sa avem optiunile de filtrare
		QDialog* dialog = new QDialog;
		dialog->setWindowTitle("Filter options");

		//dupa titlu sau an
		auto titluButton = new QPushButton("Titlu");
		auto anButton = new QPushButton("An");

		auto layoutTotal = new QVBoxLayout(dialog);

		QFormLayout* formText = new QFormLayout;
		QWidget* widForm = new QWidget;
		widForm->setLayout(formText);
		auto txtFisier = new QLineEdit;
		formText->addRow(new QLabel("Introdu titlu/an de filtrare: "), txtFisier);

		layoutTotal->addWidget(widForm);

		auto layout = new QHBoxLayout;
		layout->addWidget(titluButton);
		layout->addWidget(anButton);

		//ne am facut si un form mai sus in care introducem
		//text dupa care se filtreaza
		layoutTotal->addLayout(layout);

		//in functie de butonul apasat (titlu sau an) se executa
		//conexiunea respectiva pt butonul ala
		QObject::connect(titluButton, &QPushButton::clicked, [&]() {
			QDialog* dialogTitlu = new QDialog;
			dialogTitlu->setWindowTitle("Filtrare dupa titlu");
			QListWidget* lstFilterTitlu = new QListWidget;
			auto layoutTitlu = new QVBoxLayout(dialogTitlu);

			QWidget* wid = new QWidget;
			QVBoxLayout* vlLista = new QVBoxLayout;
			wid->setLayout(vlLista);
			vlLista->addWidget(lstFilterTitlu);

			layoutTitlu->addWidget(wid);

			QString userInput = txtFisier->text();

			bool isNumber;
			double number = userInput.toDouble(&isNumber);

			if (!isNumber) {
				auto vals = srv.filter(txtFisier->text().toStdString(), -1);
				for (const auto& f : vals) {
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.getTitlu()));
					item->setText(QString::fromStdString("Titlu: " + f.getTitlu() + " | Gen: " + f.getGen() + " | Actor: " + f.getActor() + " | An: " + std::to_string(f.getAn())));
					lstFilterTitlu->addItem(item);
				}
				dialogTitlu->exec();
			}
			else {
				QMessageBox::warning(this, "Warning", "Introdu text pentru titlu, nu numar!");
			}

			dialog->close();
			});

		QObject::connect(anButton, &QPushButton::clicked, [&]() {
			
			QDialog* dialogTitlu = new QDialog;
			dialogTitlu->setWindowTitle("Filtrare dupa titlu");
			QListWidget* lstFilterTitlu = new QListWidget;
			auto layoutTitlu = new QVBoxLayout(dialogTitlu);

			QWidget* wid = new QWidget;
			QVBoxLayout* vlLista = new QVBoxLayout;
			wid->setLayout(vlLista);
			vlLista->addWidget(lstFilterTitlu);

			layoutTitlu->addWidget(wid);

			QString userInput = txtFisier->text();

			bool isNumber;
			double number = userInput.toDouble(&isNumber);

			if (isNumber) {
				auto vals = srv.filter("", txtFisier->text().toInt());
				for (const auto& f : vals) {
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.getTitlu()));
					item->setText(QString::fromStdString("Titlu: " + f.getTitlu() + " | Gen: " + f.getGen() + " | Actor: " + f.getActor() + " | An: " + std::to_string(f.getAn())));
					lstFilterTitlu->addItem(item);
				}
				dialogTitlu->exec();
			}
			else {
				QMessageBox::warning(this, "Warning", "Introdu numar pentru an, nu text!");
			}

			dialog->close();

			});

		dialog->exec();
		});

	//conexiune pt buton raport
	QObject::connect(btnRaport, &QPushButton::clicked, [&]() {
		QDialog* dialog = new QDialog;
		dialog->setWindowTitle("Raport");

		auto layoutTotal = new QVBoxLayout(dialog);

		auto labelRaport = new QLabel("Raport nr. filme dintr-un an");

		layoutTotal->addWidget(labelRaport);

		QListWidget* lstRaport = new QListWidget;
		layoutTotal->addWidget(lstRaport);

		const auto& map = srv.frecventaAn(srv.getAll());
		for (const auto& pereche : map) {
			DTO per = pereche.second;
			QListWidgetItem* item = new QListWidgetItem;
			item->setText(QString::fromStdString("Pentru anul " + std::to_string(pereche.first) + " sunt " + std::to_string(per.getCount()) + " filme"));
			lstRaport->addItem(item);
		}
		dialog->exec();
		});

	//conexiune pt lista (selectare de item)
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto select = lst->selectedItems();
		if (select.isEmpty()) {
			resetForm();
			btnAddToRent->setDisabled(true);
		}
		else {
			auto selectItem = select.at(0);
			auto titlu = selectItem->data(Qt::UserRole + 1).toString();
			auto gen = selectItem->data(Qt::UserRole + 2).toString();
			auto actor = selectItem->data(Qt::UserRole + 3).toString();
			auto an = selectItem->data(Qt::UserRole + 4).toInt();
			qDebug() << titlu << " " << gen << " " << actor << " " << an;
			txtTitlu->setText(titlu);
			txtGen->setText(gen);
			txtActor->setText(actor);
			txtAn->setText(QString::number(an));
			btnAddToRent->setEnabled(true);
		}
		});
	
	//conexiune pt buton adauga rent
	QObject::connect(btnAddToRent, &QPushButton::clicked, this, [&]() {
		auto select = lst->selectedItems();
		if (!select.isEmpty()) {
			auto selectItem = select.at(0);
			auto titlu = selectItem->data(Qt::UserRole + 1).toString();
			auto gen = selectItem->data(Qt::UserRole + 2).toString();
			auto actor = selectItem->data(Qt::UserRole + 3).toString();
			auto an = selectItem->data(Qt::UserRole + 4).toInt();
			Filme f{ titlu.toStdString(), gen.toStdString(), actor.toStdString(), an};
			srv.adaugaInchiriere(f);
			lst->clearSelection();
			resetForm();
		}
		});

}

void GUI::addNewFilme() {
	try {
		srv.add(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAn->text().toInt());
		reloadList(srv.getAll());
		resetForm();
	}
	catch(ValidateException& ex){
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (FilmeRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void GUI::stergeFilme() {
	auto titlu = txtTitlu->text().toStdString();
	
	try {
		srv.deletee(titlu);
		reloadList(srv.getAll());
		resetForm();
	}
	catch (FilmeRepoException& ex) {
		QMessageBox::critical(this, "Alert", QString::fromStdString(ex.getMsg()));
	}
}

void GUI::modificaFilme() {
	auto titlu = txtTitlu->text().toStdString();
	auto gen = txtGen->text().toStdString();
	auto actor = txtActor->text().toStdString();
	auto an = txtAn->text().toInt();

	try {
		srv.modify(titlu, gen, actor, an);
		reloadList(srv.getAll());
		resetForm();
	}
	catch (FilmeRepoException& ex) {
		QMessageBox::critical(this, "Alert", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::critical(this, "Alert", QString::fromStdString(ex.getMsg()));
	}
}

void GUI::undoFilme() {
	try {
		srv.undo();
		reloadList(srv.getAll());
	}
	catch (ValidateException& ex) {
		QMessageBox::critical(this, "Alert", QString::fromStdString(ex.getMsg()));
	}
}

void GUI::reloadList(const vector<Filme>& filme) {
	lst->clear();
	for (const auto& f : filme) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.getTitlu()));
		item->setText(QString::fromStdString("Titlu: " + f.getTitlu() + " | Gen: " + f.getGen() + " | Actor: " + f.getActor() + " | An: " + std::to_string(f.getAn())));
		item->setData(Qt::UserRole + 1, QString::fromStdString(f.getTitlu()));
		item->setData(Qt::UserRole + 2, QString::fromStdString(f.getGen()));
		item->setData(Qt::UserRole + 3, QString::fromStdString(f.getActor()));
		item->setData(Qt::UserRole + 4, f.getAn());
		lst->addItem(item);
	}
}

void GUI::resetForm() {
	txtTitlu->setText("");
	txtGen->setText("");
	txtActor->setText("");
	txtAn->setText("");
}
