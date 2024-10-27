#pragma once
#include "Filme.h"
//#include "VectorDinamicTemplate.h"
#include <vector>
#include <ostream>
#include <unordered_map>

using std::vector;
using std::ostream;

class AbsRepo {
public:

    virtual void store(const Filme& f) = 0;
    virtual void set(const string& titlu, const string& gen, const  string& actor, const  int& an) = 0;
    virtual const Filme& find(const string& titlu) const = 0;
    virtual void deleteElement(const int& f) = 0;
    virtual void swap(const size_t f1, const size_t f2) = 0;
    virtual vector<Filme> getAll() const = 0;

    virtual ~AbsRepo() = default;
};

class RepoFilme: public AbsRepo{
private:
    //valorile obiectului nostru
    //un vector ce contine obiecte de tip filme
    vector<Filme> filme;

    [[nodiscard]] bool exist(const Filme& f) const;
public:
    RepoFilme(const RepoFilme& ot) = delete;
    RepoFilme() = default;
    
    virtual void store(const Filme& f) override;
    virtual void set(const string& titlu, const string& gen, const  string& actor, const  int& an) override;
    virtual const Filme& find(const string& titlu) const override;
    virtual vector<Filme> getAll() const override;
    virtual void swap(const size_t f1, const size_t f2) override;
    virtual void deleteElement(const int& f) override;
    virtual ~RepoFilme() = default;
};

class FileRepo : public RepoFilme {
private:
    string fname;

    void load_from_file();

    void save_to_file();

public:
    FileRepo() = default;
    explicit FileRepo(string fn);

    ~FileRepo() override = default;

    void store(const Filme& f) override {
        RepoFilme::store(f);
        save_to_file();
    }

    void set(const string& titlu, const string& gen, const  string& actor, const  int& an) override {
        RepoFilme::set(titlu, gen, actor, an);
        save_to_file();
    }

    void deleteElement(const int& f) override {
        RepoFilme::deleteElement(f);
        save_to_file();
    }
};

class RepoLab : public AbsRepo {
private:
    std::unordered_map<string, Filme> elems;
    float prob;

    void det_prob() const ;
    bool exist(const Filme& f) const;

public:
    RepoLab() = default;
    explicit RepoLab(float probb) {
        this->prob = probb;
        elems.clear();
    }

    void store(const Filme& f) override;

    void set(const string& titlu, const string& gen, const  string& actor, const  int& an) override;

    const Filme& find(const string& titlu) const override;
    
    vector<Filme> getAll() const override;

    void swap(const size_t f1, const size_t f2) override;
    void deleteElement(const int& f) override;

    ~RepoLab() override = default;

};


//exceptii repo
class FilmeRepoException {
    string msg;
public:
    FilmeRepoException(const string& m) : msg{ m } {}
    string getMsg()const { return msg; }
    friend ostream& operator<<(ostream& out, const FilmeRepoException& ex);
};

ostream& operator<<(ostream& out, const FilmeRepoException& ex);

void testRepo();
void testFind();
void testRepoLab();
