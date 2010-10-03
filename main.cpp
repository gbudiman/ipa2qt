#include "ipacl.h"
#include "ipaShape.h"

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <QtGui>
#include <QApplication>
#include <QList>
#include <vector>
#include <sstream>
using namespace std;

dw::dw(QWidget* parent) : QWidget(parent) {
	setMouseTracking(true);
	shape = 0;
	color = 0;
	onWidget = 0;
	setAttribute(Qt::WA_PaintOutsidePaintEvent,true);
	formSaved = true;
	QList<ipaShape> shapeContainer;
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
	QPainter painter(this);

	for (int i = 0; i < shapeContainer.size(); i++) {
		switch (shapeContainer.at(i).color) {
		case 0: painter.setBrush(Qt::red); break;
		case 1: painter.setBrush(Qt::green); break;
		default: painter.setBrush(Qt::blue);
		}
		switch (shapeContainer.at(i).shape) {
		case 0: painter.drawEllipse(shapeContainer.at(i).x-30,shapeContainer.at(i).y-30,60,60); break;
		case 1: painter.drawRect(QRect(shapeContainer.at(i).x - 30,shapeContainer.at(i).y - 30,60,60)); break;
		default: QVector<QPoint> polyPoints;
			polyPoints << QPoint(shapeContainer.at(i).x-30, shapeContainer.at(i).y+26)
					<< QPoint(shapeContainer.at(i).x, shapeContainer.at(i).y-26)
					<< QPoint(shapeContainer.at(i).x+30, shapeContainer.at(i).y+26);
			painter.drawPolygon(polyPoints);
		}
	}

	if (onWidget == 1) {
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
		painter.setBrush(Qt::transparent);
		painter.drawEllipse(900, 900, 1, 1);
	}
}

void dw::fixPaint(int x, int y) {
	ipaShape ds(x, y, shape, color);
	shapeContainer.append(ds);
	formSaved = false;

	/*for (int i = 0; i < shapeContainer.size(); i++) {
		cout << shapeContainer.at(i).x << shapeContainer.at(i).y << shapeContainer.at(i).shape << shapeContainer.at(i).color << endl;
	}*/

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

void dw::save() {
	ofstream f;
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Form"), QDir::currentPath());
	if (filename != "") {
		f.open(filename.toLocal8Bit());
		for (int i = 0; i < shapeContainer.size(); i++) {
			f << shapeContainer.at(i).x << " ";
			f << shapeContainer.at(i).y << " ";
			f << shapeContainer.at(i).shape << " ";
			f << shapeContainer.at(i).color << "\n";
		}
		f.close();
		formSaved = true;
	}
}

void dw::readFile(QString fileToRead) {
	string line;
	shapeContainer.clear();
	int dataX;
	int dataY;
	int dataShape;
	int dataColor;

	string dummy;
	ifstream myfile(fileToRead.toLocal8Bit());
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			getline(myfile, line);
			//cout << line << endl;
			if (!myfile.eof()) {
				stringstream ss(line);

				ss >> dataX;
				ss >> dataY;
				ss >> dataShape;
				ss >> dataColor;
				//cout << dataX << " " << dataY << " " << dataShape << " " << dataColor << endl;
				ipaShape ds(dataX, dataY, dataShape, dataColor);
				shapeContainer.append(ds);
			}
		}
	}
	update();
}

void dw::open() {
	if (formSaved) {
		QString rFile = QFileDialog::getOpenFileName(this, tr("Open Form"), QDir::currentPath());
		readFile(rFile);
	}
	else {
		QMessageBox askToSave;
		askToSave.setWindowTitle("Save Form?");
		askToSave.setIcon(QMessageBox::Information);
		askToSave.setText("Do you want to save the changes to this document before closing?");
		askToSave.setInformativeText("If you don't save, your changes will be lost.");
		askToSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		askToSave.setDefaultButton(QMessageBox::Save);
		int openRet = askToSave.exec();

		switch (openRet) {
		case QMessageBox::Save: save();
								readFile(QFileDialog::getOpenFileName(this, tr("Open Form"), QDir::currentPath()));
								formSaved = true;
								break;
		case QMessageBox::Discard: shapeContainer.clear();
									update();
									readFile(QFileDialog::getOpenFileName(this, tr("Open Form"), QDir::currentPath()));
									formSaved = true;
									break;
		case QMessageBox::Cancel: break;
		}
	}
}

void dw::newFile() {
	if (formSaved) {
		shapeContainer.clear();
		update();
	}
	else {
		QMessageBox askToSave;
		askToSave.setWindowTitle("Save Form?");
		askToSave.setIcon(QMessageBox::Information);
		askToSave.setText("Do you want to save the changes to this document before closing?");
		askToSave.setInformativeText("If you don't save, your changes will be lost.");
		askToSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		askToSave.setDefaultButton(QMessageBox::Save);
		int newRet = askToSave.exec();

		switch (newRet) {
		case QMessageBox::Save: save();
								formSaved = true;
								break;
		case QMessageBox::Discard: shapeContainer.clear();
									update();
									formSaved = true;
									break;
		case QMessageBox::Cancel: break;
		}
	}
}

void dw::close() {
	if (formSaved) {
		qApp->exit(0);
	}
	else {
		QMessageBox askToSave;
		askToSave.setWindowTitle("Exit Designer?");
		askToSave.setIcon(QMessageBox::Information);
		askToSave.setText("Do you want to save the changes to this document before closing?");
		askToSave.setInformativeText("If you don't save, your changes will be lost.");
		askToSave.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		askToSave.setDefaultButton(QMessageBox::Save);
		int exitRet = askToSave.exec();

		switch (exitRet) {
		case QMessageBox::Discard: qApp->exit(0); break;
		case QMessageBox::Save: save(); qApp->exit(0); break;
		}
	}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPACL w;
    w.show();
    w.setWindowTitle("IPA2::MainWindow");
    return a.exec();
}
