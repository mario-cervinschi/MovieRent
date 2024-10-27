#pragma once
#include "Service.h"
#include "inchirieri.h"
class UI
{
private:
    //valorile obiectului nostru
    //contine service ul programului nostru

    Service& serv;
    void auto_addStart();
    void menu();
    void add_menu();
    void delete_menu();
    void modify_menu();
    void cauta_menu();
    void filter_menu();
    void sort_menu();
    void rent();
    void raport(const vector<Filme>& filme);
    void undoUI();
public:
    //constructorul

    UI(Service& serv) noexcept : serv{ serv } {
    }
    void start();
    void print(const vector<Filme>& filme);

};

