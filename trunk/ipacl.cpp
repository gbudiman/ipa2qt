#include <QtGui>
#include "ipacl.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

IPACL::IPACL(QWidget *parent)
    : QMainWindow(parent)
{
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
	connect(drawingWidget, SIGNAL(mouseFollow(int, int)), this, SLOT(update()));
	connect(drawingWidget, SIGNAL(mouseClicked(int, int)), drawingWidget, SLOT(fixPaint(int, int)));
	connect(drawingWidget, SIGNAL(mouseLeaving()), drawingWidget, SLOT(update()));

	/*
	 * Create Mouse Position Tracker
	 */
	QHBoxLayout* layout = new QHBoxLayout;
	mousePosLabel = new QLabel(tr("Mouse pos here"));

	QGroupBox* mGroup = new QGroupBox();
	QVBoxLayout* mbox = new QVBoxLayout;
	/*
	 * Create Shape Group
	 */
	QGroupBox* shapeGroup = new QGroupBox(tr("Shape"));
	QRadioButton* radioCircle = new QRadioButton(tr("Circle"));
	connect(radioCircle, SIGNAL(clicked()), this, SLOT(radioSetCircle()));
	connect(radioCircle, SIGNAL(clicked()), drawingWidget, SLOT(setToCircle()));
	QRadioButton* radioSquare = new QRadioButton(tr("Square"));
	connect(radioSquare, SIGNAL(clicked()), this, SLOT(radioSetSquare()));
	connect(radioSquare, SIGNAL(clicked()), drawingWidget, SLOT(setToSquare()));
	QRadioButton* radioTriangle = new QRadioButton(tr("Triangle"));
	connect(radioTriangle, SIGNAL(clicked()), this, SLOT(radioSetTriangle()));
	connect(radioTriangle, SIGNAL(clicked()), drawingWidget, SLOT(setToTriangle()));
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
	connect(radioRed, SIGNAL(clicked()), drawingWidget, SLOT(setToRed()));
	QRadioButton* radioGreen = new QRadioButton(tr("Green"));
	connect(radioGreen, SIGNAL(clicked()), this, SLOT(radioSetGreen()));
	connect(radioGreen, SIGNAL(clicked()), drawingWidget, SLOT(setToGreen()));
	QRadioButton* radioBlue = new QRadioButton(tr("Blue"));
	connect(radioBlue, SIGNAL(clicked()), this, SLOT(radioSetBlue()));
	connect(radioBlue, SIGNAL(clicked()), drawingWidget, SLOT(setToBlue()));
	QVBoxLayout* wbox = new QVBoxLayout;
	wbox->addWidget(radioRed);
	wbox->addWidget(radioGreen);
	wbox->addWidget(radioBlue);
	colorGroup->setLayout(wbox);

	radioRed->setChecked(true);

	layout->addWidget(drawingWidget);
	mbox->addWidget(mousePosLabel);
	mbox->addWidget(shapeGroup);
	mbox->addWidget(colorGroup);
	mGroup->setLayout(mbox);
	layout->addWidget(mGroup);
	widget->setLayout(layout);

	//setLayout(vbox);

	createActions();
	createMenus();

	connect(circleAct, SIGNAL(triggered()), drawingWidget, SLOT(setToCircle()));
	connect(circleAct, SIGNAL(triggered()), radioCircle, SLOT(click()));
	connect(squareAct, SIGNAL(triggered()), drawingWidget, SLOT(setToSquare()));
	connect(squareAct, SIGNAL(triggered()), radioSquare, SLOT(click()));
	connect(triangleAct, SIGNAL(triggered()), drawingWidget, SLOT(setToTriangle()));
	connect(triangleAct, SIGNAL(triggered()), radioTriangle, SLOT(click()));

	connect(newAct, SIGNAL(triggered()), drawingWidget, SLOT(newFile()));
	connect(openAct, SIGNAL(triggered()), drawingWidget, SLOT(open()));
	connect(exitAct, SIGNAL(triggered()), drawingWidget, SLOT(close()));
	connect(saveAct, SIGNAL(triggered()), drawingWidget, SLOT(save()));
	//QPoint t = QCursor::pos();
	//cout << t.x() << " " << t.y() << endl;
	resize(600, 480);
}

IPACL::~IPACL()
{

}

void IPACL::draw(int x, int y) {
	cout << "Will draw at " << x << ", " << y << endl;
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
}

void IPACL::createActions() {
	newAct = new QAction(tr("New"), this);
	openAct = new QAction(tr("Open"), this);
	saveAct = new QAction(tr("Save"), this);
	exitAct = new QAction(tr("Exit"), this);
	circleAct = new QAction(tr("Circle"), this);
	squareAct = new QAction(tr("Square"), this);
	triangleAct = new QAction(tr("Triangle"), this);
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
}

void IPACL::mousePosition() {
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
}

void IPACL::radioSetGreen() {
}

void IPACL::radioSetBlue() {
}

void IPACL::radioSetSquare() {
}

void IPACL::radioSetTriangle() {
}

void IPACL::radioSetCircle() {
}

void IPACL::setSquare() {
}

void IPACL::setTriangle() {
}

void IPACL::setCircle() {
}
