
#include "Filme.h"
#include <assert.h>
int Filme::getAn() const noexcept
{
    //returneaza anul obiectului 'film'
    return this->an;
}

string Filme::getActor() const
{
    //returneaza actorul obiectului 'film'
    return this->actor;
}

string Filme::getGen() const
{
    //returneaza genul obiectului 'film'
    return this->gen;
}

string Filme::getTitlu() const
{
    //returneaza titlul obiectului 'film'
    return this->titlu;
}

void Filme::setTitlu(const string& titluu)
{
    //param: titluu - titlul unui film
    //seteaza titlul obiectului 'film' cu cel primit ca parametru
    this->titlu = titluu;
}

void Filme::setGen(const string& genn)
{
    //param: genn - genul unui film
    //seteaza genul obiectului 'film' cu cel primit ca parametru
    this->gen = genn;
}

void Filme::setActor(const string& actorr)
{
    //param: actorr - actorul unui film
    //seteaza actorul obiectului 'film' cu cel primit ca parametru
    this->actor = actorr;
}

void Filme::setAn(const int& ann) noexcept
{
    //param: ann - anul unui film
    //seteaza anul obiectului 'film' cu cel primit ca parametru
    this->an = ann;
}

Filme& Filme::operator=(const Filme& ot) = default;

bool Filme::operator==(const Filme& ot) const{
    if (an == ot.an && actor == ot.actor && gen == ot.gen && titlu == ot.titlu) {
        return true;
    }
    return false;
}

void testFilme() {
    Filme f{ "daad", "ggg", "fdss", 3333 };
    assert(f.getActor() == "fdss");
    assert(f.getTitlu() == "daad");
    assert(f.getGen() == "ggg");
    assert(f.getAn() == 3333);
    f.setActor("aaaa");
    f.setTitlu("kkkk");
    f.setGen("ddd");
    f.setAn(2222);
    assert(f.getActor() == "aaaa");
    assert(f.getTitlu() == "kkkk");
    assert(f.getGen() == "ddd");
    assert(f.getAn() == 2222);
}