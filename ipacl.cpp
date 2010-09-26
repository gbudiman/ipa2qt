#include <QtGui>
#include "ipacl.h"
#include <iostream>
#include <string>
using namespace std;

IPACL::IPACL(QWidget *parent)
    : QMainWindow(parent)
{
	//ui.setupUi(this);
	formSaved = false;
	createActions();
	createMenus();
	resize(600, 480);
}

IPACL::~IPACL()
{

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

void IPACL::save() {
	formSaved = true;
}

void IPACL::open() {
	string needSave = "Do you want to save the changes to this document before closing?<br /><br />If you don't save, your changes will be lost.";

	if (formSaved) {
		QString directory = QFileDialog::getExistingDirectory(this, tr("Open Form"), QDir::currentPath());
	}
	else {
		//QMessageBox::QMessageBox(this, needSave, QMessageBox::Close, QMessageBox::Cancel, QMessageBox::Save);
	}
}

void IPACL::newFile() {
	//QMessageBox::QMessageBox(this, "Form saved", "Form saved", QMessageBox::Ok, QMessageBox::Ignore, QMessageBox::Ignore);
}

void IPACL::close() {
	qApp->exit(0);
}
