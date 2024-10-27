#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include "FilmeGUI.h"
#include "FilmeGUIModele.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include "UI.h"

void test_all() {
	testRepo();
	testFind();
	testRepoLab();
	testFilme();
	testServ();
	testValidator();
	inchirieriTests();
}

int main(int argc, char *argv[])
{
	test_all();

	QApplication a(argc, argv);

	FileRepo rep{ "data.txt" };
	FilmeValidator valid;
	inchirieri rent;
	Service srv{ rep, valid, rent };

	FilmeGUIModele gui{ srv };
	
	//RentGUI* rentGUI = new RentGUI{ srv };
	//rentGUI->move(200, 300);
	gui.show();
	//rentGUI->show();

    return a.exec();
}
