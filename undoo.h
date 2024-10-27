#pragma once

#include "RepoFilme.h"

class ActUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActUndo() = default;
};

class UndoAdd :public ActUndo {
private:
	AbsRepo& rep;
	Filme last;
public:
	UndoAdd(AbsRepo& f, const Filme& last): rep{f}, last{last}{}
	void doUndo() override {
		int i = 0;
		for (auto& it : rep.getAll()) {
			if (it == last) {
				break;
			}
			++i;
		}
		rep.deleteElement(i);
	}
};

class UndoMod : public ActUndo {
private:
	AbsRepo& rep;
	Filme last;
public:
	UndoMod(AbsRepo& fil, const Filme& f) : rep{ fil }, last{ f } {}
	void doUndo() override {
		rep.set(last.getTitlu(), last.getGen(), last.getActor(), last.getAn());
	}
};

class UndoDel : public ActUndo {
private:
	AbsRepo& rep;
	Filme last;
	int poz;
public:
	UndoDel(AbsRepo& fil, const Filme& f, const int poz) : rep{ fil }, last{ f }, poz{ poz } {}
	void doUndo() override {
		rep.store(last);
	}
};