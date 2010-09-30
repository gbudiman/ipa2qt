#include <QtGui>
#include "ipacl.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

IPACL::IPACL(QWidget *parent)
    : QMainWindow(parent)
{
	//ui.setupUi(this);
	formSaved = false;

	QWidget *widget = new QWidget;
	setCentralWidget(widget);

	/*
	 * Create drawing widget
	 */
	dw* drawingWidget = new dw;
	drawingWidget->setMaximumSize(400, 400);
	drawingWidget->setMinimumSize(400, 400);
	drawingWidget->setMouseTracking(true);
	connect(drawingWidget, SIGNAL(mouseMoved(int, int)), this, SLOT(getMouseLocation(int, int)));
	/*QPainter painter(drawingWidget);
	painter.setPen(pen);
	painter.setBrush(brush);
	QRect rect(10,20,80,60);
	painter.drawRect(rect);
	painter.setWindow(10, 10, 400, 400);*/

	/*
	 * Create Mouse Position Tracker
	 */
	QVBoxLayout* layout = new QVBoxLayout;
	mousePosLabel = new QLabel(tr("Mouse pos here"));
	shapeLabel = new QLabel(tr("Shape to draw"));
	colorLabel = new QLabel(tr("Color to draw"));

	/*
	 * Create Shape Group
	 */
	QGroupBox* shapeGroup = new QGroupBox(tr("Shape"));
	QRadioButton* radioCircle = new QRadioButton(tr("Circle"));
	connect(radioCircle, SIGNAL(clicked()), this, SLOT(radioSetCircle()));
	QRadioButton* radioSquare = new QRadioButton(tr("Square"));
	connect(radioSquare, SIGNAL(clicked()), this, SLOT(radioSetSquare()));
	QRadioButton* radioTriangle = new QRadioButton(tr("Triangle"));
	connect(radioTriangle, SIGNAL(clicked()), this, SLOT(radioSetTriangle()));
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(radioCircle);
	vbox->addWidget(radioSquare);
	vbox->addWidget(radioTriangle);
	shapeGroup->setLayout(vbox);

	radioCircle->setChecked(true);

	/*
	 * Create Color Group
	 */
	QGroupBox* colorGroup = new QGroupBox(tr("Color"));
	QRadioButton* radioRed = new QRadioButton(tr("Red"));
	connect(radioRed, SIGNAL(clicked()), this, SLOT(radioSetRed()));
	QRadioButton* radioGreen = new QRadioButton(tr("Green"));
	connect(radioGreen, SIGNAL(clicked()), this, SLOT(radioSetGreen()));
	QRadioButton* radioBlue = new QRadioButton(tr("Blue"));
	connect(radioBlue, SIGNAL(clicked()), this, SLOT(radioSetBlue()));
	QVBoxLayout* wbox = new QVBoxLayout;
	wbox->addWidget(radioRed);
	wbox->addWidget(radioGreen);
	wbox->addWidget(radioBlue);
	colorGroup->setLayout(wbox);

	radioRed->setChecked(true);

	layout->addWidget(drawingWidget);
	layout->addWidget(mousePosLabel);
	layout->addWidget(shapeLabel);
	layout->addWidget(colorLabel);
	layout->addWidget(shapeGroup);
	layout->addWidget(colorGroup);
	widget->setLayout(layout);

	//setLayout(vbox);

	createActions();
	createMenus();

	//QPoint t = QCursor::pos();
	//cout << t.x() << " " << t.y() << endl;
	resize(600, 480);
}

IPACL::~IPACL()
{

}

dw::dw(QWidget* parent) : QWidget(parent) {
	setMouseTracking(true);
}

void dw::leaveEvent(QEvent* event) {
}

void dw::enterEvent(QEvent* event) {
}

void dw::mouseMoveEvent(QMouseEvent* event) {
	//cout << event->x() << ", " << event->y() << endl;
	mousePosX = event->x();
	mousePosY = event->y();
	emit mouseMoved(mousePosX, mousePosY);
	//mousePosLabel->setText("haf");
}

void IPACL::getMouseLocation(int x, int y) {
	//cout << x << ", " << y << endl;
	//stringstream s;
	//s << x << ", " << y;
	char s [50];
	sprintf(s, "%d, %d", x, y);
	QString qs(s);

	mousePosLabel->setText(qs);
}

void IPACL::leaveEvent(QEvent* event) {
	//cout << "L" << endl;
}

void IPACL::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::green);
	painter.drawRect(QRect(120,120,40,40));
}

void IPACL::createActions() {
	newAct = new QAction(tr("New"), this);
	connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
	openAct = new QAction(tr("Open"), this);
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
	saveAct = new QAction(tr("Save"), this);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
	exitAct = new QAction(tr("Exit"), this);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
	circleAct = new QAction(tr("Circle"), this);
	connect(circleAct, SIGNAL(triggered()), this, SLOT(setCircle()));
	squareAct = new QAction(tr("Square"), this);
	connect(squareAct, SIGNAL(triggered()), this, SLOT(setSquare()));
	triangleAct = new QAction(tr("Triangle"), this);
	connect(triangleAct, SIGNAL(triggered()), this, SLOT(setTriangle()));
	aboutAct = new QAction(tr("About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void IPACL::createMenus() {
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	shapeMenu = menuBar()->addMenu(tr("Shape"));
	shapeMenu->addAction(circleAct);
	shapeMenu->addAction(squareAct);
	shapeMenu->addAction(triangleAct);

	helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(aboutAct);

	/*drawingWidget = new QWidget(this);
	drawingWidget->setGeometry(QRect(10, 10, 400, 400));
	drawingWidget->setMinimumSize(400, 400);
	drawingWidget->setMaximumSize(400, 400);
	QPalette drawingPalette;
	drawingPalette.setColor(drawingWidget->backgroundRole(), "blue");
	drawingWidget->setPalette(drawingPalette);*/
}

void IPACL::mousePosition() {
	mousePosLabel->setText("gd");
}

void IPACL::about() {
	QMessageBox::about(this, tr("IPA2")
			, tr("ECE 462 Fall 2010<br />Gloria Budiman<br />gbudiman"));
}

void IPACL::square() {

}

void IPACL::triangle() {

}

void IPACL::circle() {

}

void IPACL::radioSetRed() {
	colorLabel->setText("red");
}

void IPACL::radioSetGreen() {
	colorLabel->setText("green");
}

void IPACL::radioSetBlue() {
	colorLabel->setText("blue");
}

void IPACL::radioSetSquare() {
	shapeLabel->setText("square");
}

void IPACL::radioSetTriangle() {
	shapeLabel->setText("triangle");
}

void IPACL::radioSetCircle() {
	shapeLabel->setText("circle");
}

void IPACL::save() {
	formSaved = true;
}

void IPACL::setSquare() {
	//radioSquare->setChecked(true);
	shapeLabel->setText("menu::Square");
}

void IPACL::setTriangle() {
	shapeLabel->setText("menu::Triangle");
}

void IPACL::setCircle() {
	shapeLabel->setText("menu::Circle");
}

void IPACL::open() {
	if (formSaved) {
		QString directory = QFileDialog::getExistingDirectory(this, tr("Open Form"), QDir::currentPath());
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
		case QMessageBox::Save: cout << "Save clicked" << endl; break;
		case QMessageBox::Discard: cout << "Discard" << endl; break;
		case QMessageBox::Cancel: cout << "Cancel clicked" << endl; break;
		}
	}
}

void IPACL::newFile() {
	if (formSaved) {
		// Create new blank widget
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
		case QMessageBox::Save: cout << "Save clicked" << endl; break;
		case QMessageBox::Discard: cout << "Discard" << endl; break;
		case QMessageBox::Cancel: cout << "Cancel clicked" << endl; break;
		}
	}
}

void IPACL::close() {
	qApp->exit(0);
}
