
#include "RepoFilme.h"
#include <assert.h>
#include <sstream>
#include <utility>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::stringstream;

//param: f - un obiect de tip film
//adauga in vectorul actual filmul primit ca parametru
void RepoFilme::store(const Filme& f) {
    if (exist(f)) {
        throw FilmeRepoException("Exista deja filmul cu titlul" + f.getTitlu());
    }
    this->filme.push_back(f);
}

//param: f - un obiect de tip film
//verifica daca exista filmul f in vector
//returneaza: true daca exista, false altfel
bool RepoFilme::exist(const Filme& f) const {
    
    try {
        find(f.getTitlu());
        return true;
    }
    catch (FilmeRepoException&) {
        return false;
    }
}

//se ocupa de stergerea unui film
//param: f - filmul de sters
void RepoFilme::deleteElement(const int& poz) {
    filme.erase(filme.begin() + poz);
}

//operatorul pentru a da output la mesajul de eroare (in consola)   
ostream& operator<<(ostream& out, const FilmeRepoException& ex) {
    out << ex.msg;
    return out;
}

void RepoFilme::set(const string& titlu, const string& gen, const  string& actor, const  int& an)
{
    Filme f1 = find(titlu);
    for (auto& f : filme) {
        if (f.getTitlu() == titlu) {
            f.setActor(actor);
            f.setGen(gen);
            f.setAn(an);
            return; } } }

void RepoFilme::swap(const size_t index1, const size_t index2)
{
    //param: f1, f2 - doua obiecte filme
    //interschimba valorile f1 si f2
    if (index1 >= filme.size() || index2 >= filme.size()) {
        // Handle index out of range error
        return;
    }

    Filme aux = filme[index1];
    filme[index1] = filme[index2];
    filme[index2] = aux;
}

const Filme& RepoFilme::find(const string& titlu) const  {
    //param: titlu - cautare film dupa titlu
    //returneaza obiectul de tip film gasit
    //daca nu este gasit, atunci arucna exceptie
    std::vector<Filme>::const_iterator it = std::find_if(filme.begin(), filme.end(),
        [&](const Filme& a) noexcept { return a.getTitlu() == titlu; });

    if (it != filme.end()) {
        return *it;
    }
    throw FilmeRepoException("Nu exista film " + titlu);
}

vector<Filme> RepoFilme::getAll() const {
    //returneaza vectorul ce contine obiectele filme
    return filme;
}

FileRepo::FileRepo(string fn) {
    this->fname = fn;
    load_from_file();
}

void FileRepo::load_from_file() {
    ifstream fin(fname);
    string str;
    while (std::getline(fin, str)) {
        stringstream ss(str);
        string word;
        vector<string> f;

        while (std::getline(ss, word, ';')) {
            f.push_back(word);
        }
        int nr = 0;
        for (auto& ch : f[3]) {
            nr = nr * 10 + (ch - '0');
        }
        RepoFilme::store(Filme(f[0], f[1], f[2], nr));
    }
    fin.close();
}

void FileRepo::save_to_file() {
    ofstream fout(fname);
    for (auto& it : RepoFilme::getAll()) {
        fout << it.getTitlu() << ";" << it.getGen() << ";" << it.getActor() << ";" << it.getAn() << "\n";
    }
    fout.close();
}



void testRepo() {
    RepoFilme rep;
    Filme f{ "Alba", "Teatru", "Bob", 2011 };
    rep.store(f);
    auto filme = rep.getAll();
    try {
        rep.store(f);
        assert(false);
    }
    catch (const FilmeRepoException&){
        assert(true);
    }
    

    assert(filme.size() == 1);
    try {
        rep.find("c");
        assert(false);
    }
    catch (const FilmeRepoException& e) {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void testFind() {
    RepoFilme rep;
    Filme f{ "Alba", "Teatru", "Bob", 2011 };
    rep.store(f);
    try {
        rep.find("Alba");
        assert(true);
    }
    catch (const FilmeRepoException&) {
        assert(false);
    }

    try {
        rep.find("gga");
        assert(false);
    }
    catch (const FilmeRepoException&) {
        assert(true);
    }

    FileRepo repo{ "test_output.txt" };
    repo.store(f);
    repo.set(f.getTitlu(), "dada", "dada", 3);
    assert(repo.getAll().size() == 1);
    repo.deleteElement(0);
    repo.store(f);

    FileRepo repo2{ "test_output.txt" };
    auto all = repo2.getAll();
    assert(repo2.getAll().size() == 1);
    assert(repo2.getAll()[0].getTitlu() == "Alba");
    repo2.deleteElement(0);
    assert(repo2.getAll().empty());
}
