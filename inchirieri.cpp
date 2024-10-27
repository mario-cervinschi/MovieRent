#include "inchirieri.h"
#include <random>
#include <fstream>
#include <assert.h>

using std::ofstream;

inchirieri::inchirieri() {
	elems.clear();
}

void inchirieri::add_to_rent(const Filme& f) {
	elems.push_back(f);
    notify();
}

void inchirieri::empty_rent_nonobs() {
    elems.clear();
}

void inchirieri::empty_rent() {
	elems.clear();
    notify();
}

void inchirieri::random_add(const vector<Filme>& filme, const int& k) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, static_cast<int>(filme.size()) - 1);
    for (int i = 0; i < k; ++i) {
        const int nr = dist(mt);
        add_to_rent(filme[nr]);
    }
    notify();
}

void inchirieri::save_to_file(const string& fname) {
    ofstream out(fname);
    out << "Nrcrt. | Nume | Prod | Subst | Pret\n";
    int i = 0;
    for (auto& med : elems) {
        out << i++ << " " << med.getTitlu() << " " << med.getGen() << " " << med.getActor() << " " << med.getAn() << "\n";
    }
}

vector<Filme> inchirieri::get_all() const {
    return elems;
}

void inchirieriTests() {
    inchirieri r;

    Filme f{ "Alba", "Teatru", "Bob", 2011 };

    r.add_to_rent(f);
    vector<Filme> rep;
    rep = r.get_all();
    assert(rep.size() == 1);
    assert(rep[0].getActor() == "Bob");
    assert(rep[0].getAn() == 2011);
    assert(rep[0].getGen() == "Teatru");
    assert(rep[0].getTitlu() == "Alba");

    r.add_to_rent(f);
    rep = r.get_all();
    assert(rep.size() == 2);

    r.empty_rent();
    rep = r.get_all();
    assert(rep.empty());

    rep.clear();
    rep.push_back(f);
    r.random_add(rep, 2);
    assert(r.get_all().size() == 2);

    r.save_to_file("test_output.html");
    std::ifstream file("test_output.html");
    assert(file.is_open());
    file.close();
}