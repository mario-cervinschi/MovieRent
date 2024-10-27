#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab1011qtgui.h"

class lab1011qtgui : public QMainWindow
{
    Q_OBJECT

public:
    lab1011qtgui(QWidget *parent = nullptr);
    ~lab1011qtgui();

private:
    Ui::lab1011qtguiClass ui;
};
