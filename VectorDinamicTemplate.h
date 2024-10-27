#pragma once
#include <exception>

template <typename TElem>
class vectdin
{
public:
    vectdin();

    //constructor de copiere
    vectdin(const vectdin& ot); //rule of 3

    //eliberam memoria
    ~vectdin(); //rule of 3

    //op de asignare
    vectdin& operator=(const vectdin& ot); //rule of 3

    //move constructor
    vectdin(vectdin&& ot) noexcept;

    //move assignment
    vectdin& operator=(vectdin&& ot) noexcept;

    void push_back(const TElem& el);

    TElem& get(int poz) const;

    void set(int poz, const TElem& el);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] int size() const;

    void erase(const int& poz);

    TElem* begin() const;

    TElem* end() const;

private:
    int lg;
    int cap;
    TElem* elems;

    void ensureCap();
};

//constructor default
//alocam loc pt elemente

template<typename TElem>
vectdin<TElem>::vectdin()
    :elems{ new TElem[10] }, cap{ 10 }, lg{ 0 } {
}

//constructor de copiere

template<typename TElem>
vectdin<TElem>::vectdin(const vectdin<TElem>& ot) {
    elems = new TElem[ot.cap];
    //copiez elem
    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];
    }
    lg = ot.lg;
    cap = ot.cap;
}

//destructor
template<typename TElem>
vectdin<TElem>::~vectdin() {
    delete[]elems;
}

//adaugare element
//param: el - elementul de adaugat in vector
template<typename TElem>
void vectdin<TElem>::push_back(const TElem& el) {
    ensureCap();
    elems[lg++] = el;
}

//se asigura ca exista suficient spatiu de adaugare element
//daca nu exista, se mareste spatiul
template<typename TElem>
void vectdin<TElem>::ensureCap() {
    if (lg < cap)
        return;
    cap *= 2;
    auto* temp = new TElem[cap];
    for (int i = 0; i < lg; i++)
        temp[i] = elems[i];

    delete[] elems;
    elems = temp;
}

//verifica daca e gol vectorul
template<typename TElem>
bool vectdin<TElem>::empty() const {
    if (lg == 0)
        return true;
    return false;
}

//returneaza un poiter catre inceputul listei (practic iteratorul de inceput)
template<typename TElem>
TElem* vectdin<TElem>::begin() const {
    return elems;
}

//returneaza un poiter catre finalul listei (practic iteratorul de final)

template<typename TElem>
TElem* vectdin<TElem>::end() const {
    return elems + lg;
}

//se ocupa cu stergerea unui element
//param: poz - sterge elementul de pe aceasta pozitie
template<typename TElem>
void vectdin<TElem>::erase(const int& poz) {
    for (int i = poz; i < lg - 1; i++) {
        elems[i] = elems[i + 1];
    }
    lg--;
}

//returneaza numarul de elemente din vector
template<typename TElem>
int vectdin<TElem>::size() const {
    return lg;
}

//returneaza elementul de pe pozitia 'poz' din vector
template<typename TElem>
TElem& vectdin<TElem>::get(int poz)const {
    return elems[poz];
}

//are rolul de copiere ( a = b )
template<typename TElem>
vectdin<TElem>& vectdin<TElem>::operator=(const vectdin<TElem>& ot) {
    if (this == &ot) {
        return *this;
    }

    delete[] elems;
    elems = new TElem[ot.cap];

    for (int i = 0; i < ot.lg; i++) {
        elems[i] = ot.elems[i];
    }

    lg = ot.lg;
    cap = ot.cap;
    return *this;
}

template<typename TElem>
vectdin<TElem>::vectdin(vectdin&& ot) noexcept {
    elems = ot.elems;
    lg = ot.lg;
    cap = ot.cap;

    ot.elems = nullptr;
    ot.lg = 0;
    ot.cap = 0;
}

template<typename TElem>
vectdin<TElem>& vectdin<TElem>::operator=(vectdin<TElem>&& ot) noexcept {
    if (this == &ot) { return *this;
    }

    delete[] elems;

    elems = ot.elems;
    lg = ot.lg;
    cap = ot.cap;

    ot.elems = nullptr;
    ot.lg = 0;
    ot.cap = 0;
    return *this;
}

//are rolul de a seta valoarea 'el' pe pozitia 'poz' daca exista
template<typename TElem>
void vectdin<TElem>::set(int poz, const TElem& el) {
    if (poz < lg)
        elems[poz] = el;
    else
        throw std::exception("NU EXISTA ASTFEL DE POZITIE");
}