#pragma once
#include <string>
#include "Filme.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	string msgs;
public:
	ValidateException(const string& errors) :msgs{ errors } {}

	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
	std::string getMsg()const { return msgs; }

};

ostream& operator<<(ostream& out, const ValidateException& ex);

class FilmeValidator {
public:
	void validate(const Filme& f);
};

void testValidator();