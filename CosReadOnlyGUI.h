#pragma once

#include <iostream>
#include <qwidget.h>
#include <qpainter.h>
#include "inchirieri.h"
#include "qdebug.h"

class HistogramGUI : public QWidget, public Observer
{
private:
	inchirieri& rent;
public:
	HistogramGUI(inchirieri& _rent) : rent{ _rent } {
		rent.addObserver(this);
	};

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		srand(time(NULL));
		for (const auto& u : rent.get_all()) {
			int x = rand() % 300;
			int y = rand() % 300;
			qDebug() << x << " " << y << "\n";
			//p.drawRect(x, y, 20, u.getAn() / 10);
			//            p.drawLine(x, y, width(), height());
			p.drawImage(x, y, QImage("sky.jpeg"));
		}

	}
};
