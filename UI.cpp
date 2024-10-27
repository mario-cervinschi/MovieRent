#include "UI.h"
#include <iostream>

using std::cin;
using std::cout;

void UI::menu() {
    //printeaza pe ecran meniul principal
    cout << "1. Adauga\n2. Sterge\n3. Modifica\n4. Afiseaza\n5. Cauta\n6. Fitrare\n7. Sortare\n8. Inchirieri\n9. Raport\n0. exit\nComanda ta: ";
}

void UI::add_menu() {
    //meniul pentru adaugare film
    string titlu;
    string gen;
    string actor;
    int an;
    cout << "Titlu: ";
    cin >> titlu;
    cout << "Gen: ";
    cin >> gen;
    cout << "Actor: ";
    cin >> actor;
    cout << "An: ";
    cin >> an;
    serv.add(titlu, gen, actor, an);
    cout << "Film adaugat\n";
}

void UI::delete_menu() {
    //meniul pentru stergere film
    string titlu;
    cout << "Stergere dupa titlu: ";
    cin >> titlu;
    const int rez = serv.deletee(titlu);
    if (rez == 1)
        cout << "S-a gasit acest film si a fost sters\n";
    else cout << "Nu s-a gasit acest film si nu a fost sters\n";
}

void UI::modify_menu() {
    //meniul pentru modifcare film
    string titlu;
    string gen;
    string actor;
    int an;
    cout << "Modifica in functie de titlu: ";
    cin >> titlu;
    cout << "Gen nou: ";
    cin >> gen;
    cout << "Actor nou: ";
    cin >> actor;
    cout << "An nou: ";
    cin >> an;
    const int rez = serv.modify(titlu, gen, actor, an);
    if (rez == 1)
        cout << "S-a gasit acest film si a fost modificat\n";
    else cout << "Nu s-a gasit acest film si nu a fost modificat\n";
}

void UI::print(const vector<Filme>& filme) {
    //meniul pentru afisare toate filme
    int i = 0;
    for (const Filme& f : filme)
    {
        cout << i << ". Titlu: " << f.getTitlu() << " | Gen: " << f.getGen() << " | Actor: " << f.getActor() << " | An: " << f.getAn() << "\n";
        i++;
    }
}

void UI::cauta_menu() {
    //meniu pentru cautare anumit film dupa titlu
    string titlu;
    cout << "Cauta dupa titlu: ";
    cin >> titlu;
    auto f = serv.findd(titlu);
    cout << "S-a gasit acest film\n";
    cout << "Titlu: " << f.getTitlu() << " | Gen: " << f.getGen() << " | Actor: " << f.getActor() << " | An: " << f.getAn() << "\n";
}

void UI::filter_menu() {
    //meniu pentru fitrare filme
    string cmd;
    cout << "Dupa ce vrei sa filtrezi( (titlu / an): ";
    cin >> cmd;
    if (cmd == "titlu") {
        string titlu;
        cout << "Titlu: ";
        cin >> titlu;
        print(serv.filter(titlu, -1));
    }
    else if (cmd == "an") {
        int an;
        cout << "An: ";
        cin >> an;
        print(serv.filter("", an));
    }
    else {
        cout << "Comanda invalida\n";
    }
}

void UI::sort_menu() {
    //meniu pentru sortare filme
    string cmd, cmd2;
    cout << "Dupa ce vrei sa sortezi (titlu / actor / an aparitie + gen (angen) ): ";
    cin >> cmd;
    cout << "Cum vrei sa sortezi (crescator/descrescator): ";
    cin >> cmd2;

    if (cmd == "titlu") {
        if (cmd2 == "crescator")
            serv.sort(serv.ordTitlu);
        else if (cmd2 == "descrescator")
            serv.sort(serv.ordTitlu, true);
    }
    else if (cmd == "actor") {
        if (cmd2 == "crescator")
            serv.sort(serv.ordActor);
        else if (cmd2 == "descrescator")
            serv.sort(serv.ordActor, true);
    }
    else if (cmd == "angen") {
        if (cmd2 == "crescator")
            serv.sort(serv.ordAnGen);
        else if (cmd2 == "descrescator")
            serv.sort(serv.ordAnGen, true);
    }
    else {
        cout << "Comanda invalida.\n";
        return;
    }
    auto filme = serv.getAll();
    for (int i = 0; i < filme.size(); i++)
        cout << i << ". Titlu: " << filme[i].getTitlu() << " | Gen: " << filme[i].getGen() << " | Actor: " << filme[i].getActor() << " | An: " << filme[i].getAn() << "\n";

}

void UI::rent() {
    cout << "Meniu pentru inchirieri\n";
    inchirieri r;
    while (true) {
        cout << "Numar de filme: " << serv.getAllInchiriere().size() << "\n";
        cout << "Operatii disponibile: \n";
        cout << "1. Adauga filme\n";
        cout << "2. Goleste inchirieri\n";
        cout << "3. Genereaza inchirieri(random)\n";
        cout << "4. Export\n";
        cout << "0. Exit\n";
        cout << "Introduceti optiunea: ";
        string cmd;
        cin >> cmd;
        if (cmd == "1") {
            print(serv.getAll());
            cout << "Scrie nr. film de adaugat: ";
            int op;
            cin >> op;
            if(op < 0 || op > serv.getAll().size()){
                cout << "Indicele trebuie sa fie un numar natural, care poate fi maxim nr de elemente al sirului - 1\n";
                continue;
            }
            serv.adaugaInchiriere(serv.getAll()[op]);
        }
        else if (cmd == "2") {
            serv.delInchiriere();
        }
        else if (cmd == "3") {
            cout << "Scrie cate filme vreis a adaugi: ";
            int op;
            cin >> op;
            if (op < 0) {
                cout << "Indicele trebuie sa fie un numar natural\n";
                continue;
            }
            serv.randomInchiriere(serv.getAll(), op);
        }
        else if (cmd == "4") {
            cout << "1. CVS sau 2. HTML?";
            int cmdd;
            cin >> cmdd;
            string ext;
            if (cmdd == 1)
                ext = ".cvs";
            else if (cmdd == 2)
                ext = ".html";
            cout << "Introdu nume fisier";
            string fname;
            cin >> fname;
            serv.savetofileInchiriere(fname + ext);
        }
        else if (cmd == "0") {
            break;
        }
        else {
            cout << "Optiune invalida\nw";
        }
    }
}

void UI::raport(const vector<Filme>& filme) {
    cout << "Raport nr. filme dintr-un an\n";
    const auto& map = serv.frecventaAn(filme);
    for (const auto& pereche : map) {
        DTO per = pereche.second;
        cout << "Pentru anul " << pereche.first << " sunt " << per.getCount() << " filme\n";
    }
}

void UI::auto_addStart() {
    serv.add("A", "Cconcert", "Bob", 2022);
    serv.add("a", "Cconcert", "Bob", 2023);
    serv.add("aa", "Cconcert", "Bob", 2024);
    serv.add("aaa", "Cconcert", "Bob", 2021);
    serv.add("aaaa", "Cconcert", "Bob", 2020);
    serv.add("aaaaa", "Cconcert", "Bob", 2019);
    serv.add("aaaaaa", "Cconcert", "Bob", 2024);
    serv.add("aaaaaaa", "Cconcert", "Bob", 2022);
    serv.add("b", "Cconcert", "Bob", 2021);
    serv.add("bb", "Cconcert", "Bob", 2023);
    serv.add("bbb", "Cconcert", "Bob", 2024);
    serv.add("bbbb", "Cconcert", "Bob", 2020);
}

void UI::undoUI() {
    serv.undo();
    cout << "Undo cu succes";
}

void UI::start() {
    //auto_addStart();
    while (true) {
        string cmd;
        menu();
        cin >> cmd;
        try{
            if (cmd == "0")
                break;
            else if (cmd == "1")
                add_menu();
            else if (cmd == "2")
                delete_menu();
            else if (cmd == "3")
                modify_menu();
            else if (cmd == "4")
                print(serv.getAll());
            else if (cmd == "5")
                cauta_menu();
            else if (cmd == "6")
                filter_menu();
            else if (cmd == "7")
                sort_menu();
            else if (cmd == "8")
                rent();
            else if (cmd == "9")
                raport(serv.getAll());
            else if (cmd == "10")
                undoUI();
            else
                cout << "Comanda invalida.\n\n";
        }
        catch (const FilmeRepoException& ex) {
            cout << ex << '\n';
        }
        catch (const ValidateException& ex) {
            cout << ex << '\n';
        }
    }
}