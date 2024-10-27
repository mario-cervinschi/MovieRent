#include "FilmeGUIModele.h"
#include "validator.h"
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qtimer.h>
#include <qdialog.h>

//initializare GUI
//creare interfata grafica frumoasa
void FilmeGUIModele::initGUI() {

	setLayout(layMain);

	//widget partea stanga
	//cu lista filmelor
	//si sortari
	QWidget* wid = new QWidget;
	QVBoxLayout* vlLista = new QVBoxLayout;
	wid->setLayout(vlLista);
	//lst = new QListWidget;
	vlLista->addWidget(tabV);

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

	btnRent = new QPushButton("Deschide cos");
	lyBtnsFilme3->addWidget(btnRent);

	vlBtnsFilme->addLayout(lyBtnsFilme3);

	btnReadOnlyRent = new QPushButton("Grafic");
	vlLista->addWidget(btnReadOnlyRent);

	btnDeleteToRent = new QPushButton("Sterge tot cos");
	vlLista->addWidget(btnDeleteToRent);

	btnRandomToRent = new QPushButton("Random cos");
	vlLista->addWidget(btnRandomToRent);



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
}

//conexiunile dintre butoane/campuri si cod
void FilmeGUIModele::connections() {


	QObject::connect(btnAdd, &QPushButton::clicked, this, &FilmeGUIModele::addNewFilme);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &FilmeGUIModele::stergeFilme);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &FilmeGUIModele::modificaFilme);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &FilmeGUIModele::undoFilme);

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

	QObject::connect(btnDeleteToRent, &QPushButton::clicked, [&]() {
		srv.delInchiriere();
		});

	QObject::connect(btnRandomToRent, &QPushButton::clicked, [&]() {
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
				srv.randomInchiriere(srv.getAll(), nr);
				dialog->close();
			}
			else {
				QMessageBox::critical(this, "Invalid", "Nr. random nu poate fi negativ/text.");
			}

			});

		dialog->exec();
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

	QObject::connect(btnRent, &QPushButton::clicked, [&]() {
		auto fereastra = new CosGUILista{ srv.getInchirieri() , srv};
		fereastra->show();
		});

	QObject::connect(btnReadOnlyRent, &QPushButton::clicked, [&]() {
		auto fereastraFig = new HistogramGUI{ srv.getInchirieri() };
		fereastraFig->show();
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
	QObject::connect(tabV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tabV->selectionModel()->selectedIndexes().isEmpty()) {
			resetForm();
			btnAddToRent->setDisabled(true);
		}
		else {
			auto selectItem = tabV->selectionModel()->selectedIndexes().at(0).row();
			auto cel0Index = tabV->model()->index(selectItem, 0);
			auto titlu = tabV->model()->data(cel0Index, Qt::DisplayRole).toString();
			auto cel1Index = tabV->model()->index(selectItem, 1);
			auto actor = tabV->model()->data(cel1Index, Qt::DisplayRole).toString();
			auto cel2Index = tabV->model()->index(selectItem, 2);
			auto gen = tabV->model()->data(cel2Index, Qt::DisplayRole).toString();
			auto cel3Index = tabV->model()->index(selectItem, 3);
			auto an = tabV->model()->data(cel3Index, Qt::DisplayRole).toInt();
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
		if (tabV->selectionModel()->selectedIndexes().isEmpty()) {
			resetForm();
			btnAddToRent->setDisabled(true);
		}
		else {
			auto titlu = txtTitlu->text();
			auto gen = txtGen->text();
			auto actor = txtActor->text();
			auto an = txtAn->text().toInt();
			Filme f{ titlu.toStdString(), gen.toStdString(), actor.toStdString(), an };
			srv.adaugaInchiriere(f);
			tabV->clearSelection();
			resetForm();
		}
		});

}

void FilmeGUIModele::addNewFilme() {
	try {
		srv.add(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAn->text().toInt());
		reloadList(srv.getAll());
		resetForm();
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (FilmeRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void FilmeGUIModele::stergeFilme() {
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

void FilmeGUIModele::modificaFilme() {
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

void FilmeGUIModele::undoFilme() {
	try {
		srv.undo();
		reloadList(srv.getAll());
	}
	catch (ValidateException& ex) {
		QMessageBox::critical(this, "Alert", QString::fromStdString(ex.getMsg()));
	}
}

void FilmeGUIModele::reloadList(const vector<Filme>& filme) {
	modelTabel->setOferte(filme);
}

void FilmeGUIModele::resetForm() {
	txtTitlu->setText("");
	txtGen->setText("");
	txtActor->setText("");
	txtAn->setText("");
}
