#include "RepoFilme.h"
#include <vector>
#include <assert.h>
using std::vector;

bool RepoLab::exist(const Filme& f) const {

    try {
        string titlu = f.getTitlu();
        Filme f2 = find(titlu);
        return true;
    }
    catch (FilmeRepoException&) {
        return false;
    }
}


void RepoLab::store(const Filme& f) {
    det_prob();

    if (exist(f)) {
        throw FilmeRepoException("Exista deja filmul cu titlul" + f.getTitlu());
    }

    elems[f.getTitlu()] = f;
}

void RepoLab::set(const string& titlu, const string& gen, const  string& actor, const  int& an) {
    det_prob();
    Filme f1 = find(titlu);
    for (auto& f : elems) {
        if (f1.getTitlu() == titlu) {
            f.second.setActor(actor);
            f.second.setGen(gen);
            f.second.setAn(an);
            return;
        }
    }
}

const Filme& RepoLab::find(const string& titlu) const {
    det_prob();

    for (auto& f : elems)
    {
        if (f.second.getTitlu() == titlu)
            return f.second;
    }
    throw FilmeRepoException("Nu exista film " + titlu);
}


vector<Filme> RepoLab::getAll() const {
    vector<Filme> toate; // Create a new vector each time

    for (const auto& elem : elems) {
        Filme f{ elem.second.getTitlu(), elem.second.getGen(), elem.second.getActor(), elem.second.getAn() };
        toate.push_back(f);
    }
    return toate;
}

void RepoLab::swap(const size_t index1, const size_t index2)
{
    det_prob();
    //param: f1, f2 - doua obiecte filme
    //interschimba valorile f1 si f2
    std::vector<std::pair<string, Filme>> elemsVector(elems.begin(), elems.end());

    // Check if the indices are valid
    if (index1 >= elemsVector.size() || index2 >= elemsVector.size()) {
        // Handle index out of range error
        return;
    }

    // Swap the elements in the vector
    std::swap(elemsVector[index1], elemsVector[index2]);

    // Clear the unordered_map and insert the elements from the modified vector
    elems.clear();
    for (const auto& pair : elemsVector) {
        elems[pair.first] = pair.second;
    }
}


void RepoLab::deleteElement(const int& f) {
    det_prob();
    int count = f;
    for (auto it = elems.begin(); it != elems.end(); ++it) {
        if (count == 0) {
            elems.erase(it);
            break; // Exit the loop after deleting the second element
        }
        count--;
    }
    std::unordered_map<string, Filme> elems2;
    elems2.clear();
    for (auto& it : elems) {
        elems2.insert({ it.second.getTitlu(), it.second});
    }
    elems = elems2;
}

void RepoLab::det_prob() const {
    auto const luck = int(prob * 10);
    const int nr = rand() % 10 + 1;
    if (nr <= luck) {
        return;
    }
    throw FilmeRepoException("Sansa proasta");
}


void testRepoLab() {
    RepoLab rep{ 1 };
    Filme f{ "Alba", "Teatru", "Bob", 2011 };
    rep.store(f);

    vector<Filme> all = rep.getAll();
    all.clear();
    assert(rep.getAll().size() == 1);
    assert(rep.getAll()[0].getTitlu() == "Alba");
    assert(rep.getAll()[0].getGen() == "Teatru");
    assert(rep.getAll()[0].getActor() == "Bob");
    assert(rep.getAll()[0].getAn() == 2011);

    //rep.deleteElement(0);
    try {
        rep.store(f);
        assert(false);
    }
    catch (const FilmeRepoException&) {
        assert(true);
    }

    rep.set("Alba", "Comedie", "Giani", 2005);
    assert(rep.getAll().size() == 1);
    assert(rep.getAll()[0].getTitlu() == "Alba");
    assert(rep.getAll()[0].getGen() == "Comedie");
    assert(rep.getAll()[0].getActor() == "Giani");
    assert(rep.getAll()[0].getAn() == 2005);

    Filme f2{ "Campie", "Drama", "Sam", 2012 };
    rep.store(f2);
    assert(rep.getAll().size() == 2);

    rep.deleteElement(0);
    assert(rep.getAll().size() == 1);

    rep.deleteElement(0);
    assert(rep.getAll().size() == 0);

    auto repno = RepoLab(0);

    rep.store(f);
    rep.store(f2);
    assert(rep.getAll()[0].getTitlu() == "Alba");
    assert(rep.getAll()[0].getGen() == "Teatru");
    assert(rep.getAll()[0].getActor() == "Bob");
    assert(rep.getAll()[0].getAn() == 2011);
    assert(rep.getAll()[1].getTitlu() == "Campie");
    assert(rep.getAll()[1].getGen() == "Drama");
    assert(rep.getAll()[1].getActor() == "Sam");
    assert(rep.getAll()[1].getAn() == 2012);
    rep.swap(0, 1);
    assert(rep.getAll()[1].getTitlu() == "Alba");
    assert(rep.getAll()[1].getGen() == "Teatru");
    assert(rep.getAll()[1].getActor() == "Bob");
    assert(rep.getAll()[1].getAn() == 2011);
    assert(rep.getAll()[0].getTitlu() == "Campie");
    assert(rep.getAll()[0].getGen() == "Drama");
    assert(rep.getAll()[0].getActor() == "Sam");
    assert(rep.getAll()[0].getAn() == 2012);

    assert(rep.getAll().size() == 2);
    rep.deleteElement(1);
    assert(rep.getAll().size() == 1);

    try {
        repno.store(f);
        assert(false);
    }
    catch (const FilmeRepoException&) {
        assert(true);
    }

}