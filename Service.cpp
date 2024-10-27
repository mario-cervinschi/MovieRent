
#include "Service.h"
#include "validator.h"
#include <exception>
#include <assert.h>
#include <fstream>

int Service::deletee(const string& titlu)
{
    //param: titlul dupa care stergem un anumit film
    //sterge un film din vector
    //returneaza: 1 daca s-a sters film
    //0 daca nu exista acel film de sters
    try {
        auto& ff = rep.find(titlu);
        auto filme = rep.getAll();

        Filme f{ ff.getTitlu(), ff.getGen(), ff.getActor(), ff.getAn() };

        auto it = std::find_if(filme.begin(), filme.end(), [&f](const auto& film) 
            {return film.getTitlu() == f.getTitlu(); }
        );
        
        if (it != filme.end()) {
            int poz = static_cast<int>(std::distance(filme.begin(), it));
            rep.deleteElement(poz);
            undo_act.push_back(std::make_unique<UndoDel>(rep, f, poz));
            return 1;
        }
        return 0;

    }
    catch (const FilmeRepoException& ex) {
        throw FilmeRepoException(ex);
    }
}

int Service::modify(const string& titlu, const  string& gen, const  string& actor, const  int& an) {
    //param: titlu - se modifica filmul cu acest titlu
    //param: gen - genul nou pt film
    //param: actor - actorul nou pt film
    //param: an - anul nou pt film
    //returneaza 1 daca se modifica filmul
    //0 daca nu exista acest film de modificat
    try {
        auto& it = rep.find(titlu);
        Filme f{ it.getTitlu(), it.getGen(), it.getActor(), it.getAn() };
        FilmeValidator v;
        v.validate({titlu, gen, actor, an});
        rep.set(titlu, gen, actor, an);
        undo_act.push_back(std::make_unique<UndoMod>(rep, f));
        return 1;
    }
    catch (const FilmeRepoException& ex) {
        throw FilmeRepoException(ex);
    }
}

Filme Service::findd(const string& titlu) {
    //param: titlu - titlul dupa care se cauta un film
    //cauta un film in vector
    //daca se gaseste, returneaza acest film
    //daca nu se gaseste, atunci arunca excepte de la find!
    Filme f = rep.find(titlu);
    return f;
}

vector<Filme> Service::filter(const string& titlu, const int& an)
{
    //param: titlu - daca an = -1 atunci se cauta toate filmele
    // ce au acest titlu
    //param: an - daca an != -1 atunci se cauta toate filmele
    // ce au acest an (titlul poate fi orice, nu conteaza in acest
    // caz)
    //se returneaza noul vector creat cu toate aceste filme
    vector<Filme> newone;
    auto allFilme = rep.getAll();
    if (an == -1)
    {
        std::copy_if(allFilme.begin(), allFilme.end(), std::back_inserter(newone),
            [&titlu](const Filme& f) { return f.getTitlu() == titlu; });
    }
    else
    {
        std::copy_if(allFilme.begin(), allFilme.end(), std::back_inserter(newone),
            [&an](const Filme& f) { return f.getAn() == an; });
    }
    return newone;
}

bool Service::ordTitlu(const Filme& f1, const Filme& f2, const bool& reverse)
{
    //param: f1, f2 - doua obiecte filme
    //param: reverse - true/false
    //functie de ordonare. by default - reverse = false
    //compara 2 titluri si returneaza valoarea de adevar
    //lexicografica
    if (!reverse)
        return f1.getTitlu() > f2.getTitlu();
    else
        return f1.getTitlu() < f2.getTitlu();
}

bool Service::ordActor(const Filme& f1, const Filme& f2, const bool& reverse)
{
    //param: f1, f2 - doua obiecte filme
    //param: reverse - true/false
    //functie de ordonare. by default - reverse = false
    //compara 2 actori si returneaza valoarea de adevar
    //lexicografica
    if (!reverse)
        return f1.getActor() > f2.getActor();
    else
        return f1.getActor() < f2.getActor();
}

bool Service::ordAnGen(const Filme& f1, const Filme& f2, const bool& reverse)
{
    //param: f1, f2 - doua obiecte filme
    //param: reverse - true/false
    //functie de ordonare. by default - reverse = false
    //compara 2 ani. daca anii sunt egali, atunci
    //compara si genul filmelor si returneaza valoarea de adevar
    //(daca anul filmului 1 e mai mic decat cel al filmului 2
    //si invers, depinde de valoarea lui reverse)
    if (!reverse)
    {
        if (f1.getAn() == f2.getAn())
            return f1.getGen() > f2.getGen();
        return f1.getAn() > f2.getAn();
    }
    else
    {
        if (f1.getAn() == f2.getAn())
            return f1.getGen() < f2.getGen();
        return f1.getAn() < f2.getAn();
    }
}

void Service::sort(bool (*func)(const Filme&, const Filme&, const bool&), const bool& reverse)
{
    //@param: *func - functie primita la apel. functii folositoare
    //		 ordAnGen, ordTitlu, ordActor
    //		 param: a se vedea ce fac in descrierea fiecareia mai sus
    //				(ordAnGen, ordTitlu, ordActor)
    //@param: reverse - daca se doreste sortarea crescator, atunci
    //				   reverse -> false. daca se doreste sortarea
    //				   descrescator, atunci reverse -> true
    //				   (dupa titlu SAU actor SAU an+gen)
    //BY DEFAULT - AL DOILEA PARAMETRU (REVERSE) ESTE OPTIONAL LA APEL,
    //FACAND IMPLICIT SORTAREA CRESCATOR. DACA SE DORESTE SORTAREA
    //DESCRESCATOR, ATUNCI TREBUIE PUS SI TRUE CA PARAMETRU.
    //ex: crescator - sort(ord_____);
    //	  descresc. - sort(ord_____, true);
    for (int i = 0; i < getAll().size() - 1; i++)
    {
        for (int j = i + 1; j < getAll().size(); j++)
        {
            auto newone = rep.getAll();
            if (func(newone[i], newone[j], reverse) == 1)
                rep.swap(i, j);
        }
    }
}

const unordered_map<int, DTO> Service::frecventaAn(const vector<Filme>& filme) {
    unordered_map<int, DTO> map;
    for (const auto& i : filme) {
        int const year = i.getAn();
        if (map.find(year) != map.end()) {
            map[year].incrementCount();
        }
        else {
            DTO dto(year);
            map[year] = dto;
        }
    }

    return map;
}

void Service::adaugaInchiriere(Filme f) {
    r.add_to_rent(f);
}

vector<Filme> Service::getAllInchiriere() {
    return r.get_all();
}

void Service::delInchiriere() {
    r.empty_rent();
}

void Service::randomInchiriere(vector<Filme> filme, int nr) {
    r.random_add(filme, nr);
}

void Service::savetofileInchiriere(string fname) {
    r.save_to_file(fname);
}

void Service::undo() {
    if (undo_act.empty()) {
        string err;
        err += "Nu exista operatii la care sa se faca undo";
        throw ValidateException(err);
    }
    undo_act.back()->doUndo();
    undo_act.pop_back();
}

void testServ() {
    RepoFilme rep;
    FilmeValidator val;
    inchirieri r;
    Service serv{ rep, val, r };

    serv.add("Alba", "Teatru", "Bob", 2011);
    assert(serv.getAll().size() == 1);

    string title = "Alb";
    try {
        serv.deletee(title);
        assert(false);
    }
    catch (FilmeRepoException&) {
        assert(true);
    }

    assert(serv.getAll().size() == 1);

    title = "Alba";
    assert(serv.deletee(title) == 1);
    assert(serv.getAll().size() == 0);

    serv.add("Alba", "Teatru", "Bob", 2011);
    serv.add("Bbbd", "Concert", "Bob", 2021);

    auto allelems = rep.getAll();
    auto it1 = allelems.begin();

    assert(serv.getAll().size() == 2);
    assert(serv.modify("Alba", "Roak", "Ttt", 2222) == 1);
    try {
        serv.modify("Bbbb", "Roak", "Ttt", 2222);
        assert(false);
    }
    catch (FilmeRepoException&) {
        assert(true);
    }

    auto allelems2 = rep.getAll();
    auto it = allelems2.begin();

    assert(it->getActor() == "Ttt");
    assert(it->getGen() == "Roak");
    assert(it->getAn() == 2222);


    it++;
    assert(it->getActor() == "Bob");
    assert(it->getGen() == "Concert");
    assert(it->getAn() == 2021);

    try {
        serv.findd("Alba");
        assert(true);
    }
    catch (const FilmeRepoException&) {
        assert(false);
    }

    try {
        serv.findd("ddddd");
        assert(false);
    }
    catch (const FilmeRepoException&) {
        assert(true);
    }

    serv.add("Allba", "Concert", "Bob", 2021);
    assert(serv.getAll().size() == 3);
    auto list = serv.filter("Alba", -1);
    assert(list.size() == 1);
    auto list2 = serv.filter("Bbbd", -1);
    assert(list2.size() == 1);
    auto list3 = serv.filter("", 2021);
    assert(list3.size() == 2);
    auto list4 = serv.filter("", 2014);
    assert(list4.size() == 0);
    list4 = serv.filter("Bob", -1);
    assert(list4.size() == 0);

    serv.sort(serv.ordTitlu);
    auto list5 = serv.getAll();
    assert(list5.size() == 3);
    assert(list5[0].getTitlu() == "Alba");
    assert(list5[1].getTitlu() == "Allba");
    assert(list5[2].getTitlu() == "Bbbd");

    serv.sort(serv.ordTitlu, true);
    auto list6 = serv.getAll();
    assert(list6.size() == 3);
    assert(list6[0].getTitlu() == "Bbbd");
    assert(list6[1].getTitlu() == "Allba");
    assert(list6[2].getTitlu() == "Alba");

    serv.sort(serv.ordActor);
    auto list7 = serv.getAll();
    assert(list7.size() == 3);
    assert(list7[0].getActor() == "Bob");
    assert(list7[1].getActor() == "Bob");
    assert(list7[2].getActor() == "Ttt");

    serv.sort(serv.ordActor, true);
    auto list8 = serv.getAll();
    assert(list8.size() == 3);
    assert(list8[0].getActor() == "Ttt");
    assert(list8[1].getActor() == "Bob");
    assert(list8[2].getActor() == "Bob");

    serv.add("Alllba", "Cconcert", "Bob", 2021);
    serv.add("Allllba", "Czoncert", "Bob", 2021);

    serv.sort(serv.ordAnGen);
    auto list9 = serv.getAll();
    assert(list9.size() == 5);
    assert(list9[0].getAn() == 2021);
    assert(list9[1].getAn() == 2021);
    assert(list9[2].getAn() == 2021);
    assert(list9[3].getAn() == 2021);
    assert(list9[4].getAn() == 2222);
    assert(list9[0].getGen() == "Cconcert");
    assert(list9[1].getGen() == "Concert");
    assert(list9[2].getGen() == "Concert");
    assert(list9[3].getGen() == "Czoncert");
    assert(list9[4].getGen() == "Roak");

    serv.sort(serv.ordAnGen, true);
    auto list10 = serv.getAll();
    assert(list10[4].getAn() == 2021);
    assert(list10[3].getAn() == 2021);
    assert(list10[2].getAn() == 2021);
    assert(list10[1].getAn() == 2021);
    assert(list10[0].getAn() == 2222);
    assert(list10[4].getGen() == "Cconcert");
    assert(list10[3].getGen() == "Concert");
    assert(list10[2].getGen() == "Concert");
    assert(list10[1].getGen() == "Czoncert");
    assert(list10[0].getGen() == "Roak");

    Filme f1{ "Dd", "fg", "fds", 2 };
    Filme f2{ "Dd2", "fg", "fds", 2 };
    serv.add("Alllllba", "Czoncert", "Bob", 2021);

    serv.add("Allllllba", "Czoncert", "Bob", 2021);

    serv.add("Alllllllba", "Czoncert", "Bob", 2021);

    serv.add("Allllllllba", "Czoncert", "Bob", 2021);

    serv.add("Alllllllllba", "Czoncert", "Bob", 2021);

    serv.add("Allllllllllba", "Czoncert", "Bob", 2021);

    serv.add("Alllllllllllba", "Czoncert", "Bob", 2021);

    auto list0 = rep.getAll();
    assert(list0.size() == 12);
    list0.erase(list0.begin() + 3);
    assert(list0.size() == 11);

    auto map = serv.frecventaAn(list0);
    assert(map[2021].getCount() == 10);
    assert(map[2222].getCount() == 1);

    Filme f{ "Alba", "Teatru", "Bob", 2011 };

    serv.adaugaInchiriere(f);
    assert(serv.getAllInchiriere().size() == 1);
    assert(serv.getAllInchiriere()[0].getActor() == "Bob");
    assert(serv.getAllInchiriere()[0].getAn() == 2011);
    assert(serv.getAllInchiriere()[0].getGen() == "Teatru");
    assert(serv.getAllInchiriere()[0].getTitlu() == "Alba");

    serv.adaugaInchiriere(f);
    assert(serv.getAllInchiriere().size() == 2);

    serv.delInchiriere();
    assert(serv.getAllInchiriere().empty());

    vector<Filme> repp;
    repp.clear();
    repp.push_back(f);
    serv.randomInchiriere(repp, 2);
    assert(serv.getAllInchiriere().size() == 2);

    serv.savetofileInchiriere("test_output.html");
    std::ifstream file("test_output.html");
    assert(file.is_open());
    file.close();

    assert(serv.getAll().size() == 12);

    serv.add("Adsdlba", "Teatru", "Bob", 2011);
    assert(serv.getAll().size() == 13);

    serv.undo();
    assert(serv.getAll().size() == 12);

    serv.add("Adsdlba", "Teatru", "Bob", 2011);
    serv.modify("Adsdlba", "Teatruuu", "Bobbb", 201111);
    auto film = serv.findd("Adsdlba");
    assert(film.getActor() == "Bobbb");
    assert(film.getGen() == "Teatruuu");
    assert(film.getAn() == 201111);

    serv.undo();
    film = serv.findd("Adsdlba");
    assert(film.getActor() == "Bob");
    assert(film.getGen() == "Teatru");
    assert(film.getAn() == 2011);

    assert(serv.getAll().size() == 13);
    serv.deletee("Adsdlba");
    assert(serv.getAll().size() == 12);
    serv.undo();
    assert(serv.getAll().size() == 13);

    RepoFilme reppp;
    FilmeValidator vall;
    inchirieri rr;
    Service servv{ reppp, vall , rr };
    try {
        servv.undo();
        assert(false);
    }
    catch (const ValidateException&) {
        assert(true);
    };
}