#pragma once
#include <string>
#include "Filme.h"
#include "RepoFilme.h"

#include "undoo.h"
#include "inchirieri.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "validator.h"

using std::unordered_map;
using std::string;
using std::unique_ptr;

class DTO {
private:
    int an;
    int count;
public:

    DTO() = default;
    DTO(int an) {
        this->an = an;
        this->count = 1;
    }

    void incrementCount() {
        this->count++;
    }

    int getCount() {
        return this->count;
    }

};

class Service
{
private:
    //valorile obiectului nostru
    //are 2, repo si validator
    //programului
    AbsRepo& rep;
    inchirieri& r;
    FilmeValidator& val;
    vector<unique_ptr<ActUndo>> undo_act;
public:

    //constructorul
    Service(AbsRepo& rep, FilmeValidator& val, inchirieri& r) : rep{ rep }, val{ val }, r{ r } {
        undo_act.clear();
    }

    Service(const Service& ot) = delete;
    Service() = default;

    void add(const string& titlu, const string& gen, const string& actor, const int& an) {
        Filme f{ titlu, gen, actor, an };
        val.validate(f);
        rep.store(f);
        undo_act.push_back(std::make_unique<UndoAdd>(rep, f));
    }

    int deletee(const string& titlu);

    int modify(const string& titlu, const  string& gen, const string& actor, const  int& an);

    Filme findd(const string& titlu);

    vector<Filme> filter(const string& titlu, const int& an);

    void sort(bool (*func)(const Filme&, const Filme&, const bool&), const bool& reverse = false);

    static bool ordTitlu(const Filme& f1, const Filme& f2, const bool& reverse);

    static bool ordActor(const Filme& f1, const Filme& f2, const bool& reverse);

    static bool ordAnGen(const Filme& f1, const Filme& f2, const bool& reverse);

    //calculeaza frecventa filmelor in functie de anul aparitiei
    const unordered_map<int, DTO> frecventaAn(const vector<Filme>& filme);

    vector<Filme> getAll() const noexcept {
        return rep.getAll();
    }

    void undo();

    void adaugaInchiriere(Filme f);
    vector<Filme> getAllInchiriere();
    void delInchiriere();
    inchirieri& getInchirieri() {
        return r;
    }
    void savetofileInchiriere(string fname);
    void randomInchiriere(vector<Filme> filme, int nr);
};

void testServ();
