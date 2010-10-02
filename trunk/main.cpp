#include "ipacl.h"

#include <string>
#include <iostream>
#include <QtGui>
#include <QApplication>
using namespace std;

dw::dw(QWidget* parent) : QWidget(parent) {
	setMouseTracking(true);
	shape = 0;
	color = 0;
	onWidget = 0;
	setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
}

void dw::leaveEvent(QEvent* event) {
	onWidget = 0;
	emit mouseLeaving();
}

void dw::enterEvent(QEvent* event) {
	onWidget = 1;
}

void dw::mouseMoveEvent(QMouseEvent* event) {
	//cout << event->x() << ", " << event->y() << endl;
	mousePosX = event->x();
	mousePosY = event->y();
	emit mouseMoved(mousePosX, mousePosY);
	emit mouseFollow(mousePosX, mousePosY);
	//mousePosLabel->setText("haf");
}

void dw::mousePressEvent(QMouseEvent* event) {
	emit mouseClicked(mousePosX, mousePosY);
}

void dw::paintEvent(QPaintEvent* event) {
	//cout << "invoked at " << mousePosX << ", " << mousePosY << " " << shape << ", " << color << endl;

	if (onWidget == 1) {
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		switch (color) {
		case 0: painter.setBrush(Qt::red); break;
		case 1: painter.setBrush(Qt::green); break;
		default: painter.setBrush(Qt::blue);
		}
		switch (shape) {
		case 0: painter.drawEllipse(mousePosX-30,mousePosY-30,60,60); break;
		case 1: painter.drawRect(QRect(mousePosX - 30,mousePosY - 30,60,60)); break;
		default: QVector<QPoint> polyPoints;
			polyPoints << QPoint(mousePosX-30, mousePosY+26) << QPoint(mousePosX, mousePosY-26) << QPoint(mousePosX+30, mousePosY+26);
			painter.drawPolygon(polyPoints);
		}
	}
	else {
		QPainter painter(this);
		painter.setPen(Qt::NoPen);
		painter.setBrush(Qt::transparent);
		painter.drawEllipse(900, 900, 1, 1);
	}
}

void dw::fixPaint(int x, int y) {
	cout << "clicked at " << x << ", " << y << endl;

	/*QPixmap pixmap(400, 400);
	QPainter p;
	p.begin(&pixmap);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::red);
	p.drawEllipse(x-30,y-30,60,60);
	p.end();
	p.save();*/
}

void dw::setToSquare() {
	shape = 1;
}

void dw::setToTriangle() {
	shape = 2;
}

void dw::setToCircle() {
	shape = 0;
}

void dw::setToBlue() {
	color = 2;
}

void dw::setToGreen() {
	color = 1;
}

void dw::setToRed() {
	color = 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPACL w;
    w.show();
    w.setWindowTitle("IPA2::MainWindow");
    return a.exec();
}
