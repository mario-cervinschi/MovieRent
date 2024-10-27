#include "validator.h"
#include <assert.h>
#include <sstream>

void FilmeValidator::validate(const Filme& f) {
	string msgs;
	if (f.getAn() <= 0) msgs += "An negativ/invalid!!! ";
	if (f.getActor().size() == 0) msgs+= "Actor vid!!! ";
	if (f.getGen().size() == 0) msgs += "Gen vid!!! ";
	if (f.getTitlu().size() == 0) msgs += "Titlu vid!!!";
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	FilmeValidator v;
	Filme f{ "","","", - 1};
	try {
		v.validate(f);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
		auto msg = ex.getMsg();
	}

}