#pragma once

#include <vector>
#include <string>
#include "Filme.h"
#include "observer.h"

using std::vector;
using std::string;

class inchirieri: public Observable
{
private:
	vector<Filme> elems;

public:
	inchirieri();

	vector<Filme> get_all() const;

	void add_to_rent(const Filme& f);

	void empty_rent();

	void random_add(const vector<Filme>& filme, const int& k);

	void empty_rent_nonobs();

	void save_to_file(const string& fname);
};

void inchirieriTests();

