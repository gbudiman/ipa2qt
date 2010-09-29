#ifndef IPACL_H
#define IPACL_H

#include <string>
#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class QAction;
class QLabel;
class QMenu;
class QGroupBox;
class QLabel;
class QVBoxLayout;
class QWidget;

class IPACL : public QMainWindow
{
    Q_OBJECT

public:
    IPACL(QWidget *parent = 0);
    ~IPACL();
    bool formSaved;

private slots:
	void newFile();
	void open();
	void save();
	void close();
	void circle();
	void triangle();
	void square();
	void about();
	void mousePosition();
	void setCircle();
	void setSquare();
	void setTriangle();

private:
    // Ui::IPACLClass ui;
    void createActions();
    void createMenus();

    QWidget *widget;

    QMenu* fileMenu;
    QMenu* shapeMenu;
    QMenu* helpMenu;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* exitAct;

    QAction* circleAct;
    QAction* squareAct;
    QAction* triangleAct;

    QAction* aboutAct;

	QWidget* drawingWidget;

	QLabel* mousePosLabel;
	QVBoxLayout *layout;
};

#endif // IPACL_H
