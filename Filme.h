
#pragma once
#include <string>
#include <iostream>
using std::string;

class Filme
{
private:
    //valorile obiectului nostru (film)
    string titlu;
    string gen;
    int an;
    string actor;

public:

    Filme() noexcept {}

    //constructorul filmelor noastre
    Filme(const string& titlu, const string& gen, const string& actor, int an) : titlu{ titlu }, gen{ gen }, actor{ actor }, an{ an } {
    }

    /*Filme(const Filme& f) :titlu{ f.titlu }, actor{ f.actor }, gen{ f.gen }, an{ f.an } {
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    }*/

    [[nodiscard]] int getAn() const noexcept;
    [[nodiscard]] string getGen() const;
    [[nodiscard]] string getTitlu() const;
    [[nodiscard]] string getActor() const;

    void setTitlu(const string& titlu);
    void setGen(const string& gen);
    void setActor(const string& actor);
    void setAn(const int& ann) noexcept;

    Filme& operator=(const Filme &ot);
    bool operator==(const Filme& ot) const;

    ~Filme() = default;
};

void testFilme();


