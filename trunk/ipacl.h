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
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QPixmap>

class QAction;
class QLabel;
class QMenu;
class QGroupBox;
class QLabel;
class QVBoxLayout;
class QWidget;
class QBrush;
class QPen;
class QPixmap;

class dw : public QWidget {
	Q_OBJECT

public:
	dw(QWidget* parent = 0);
	int mousePosX;
	int mousePosY;

signals:
	void mouseMoved(int x, int y);

protected:
	void leaveEvent(QEvent* event);
	void enterEvent(QEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
};

class IPACL : public QMainWindow
{
    Q_OBJECT

public:
    IPACL(QWidget *parent = 0);
    ~IPACL();
    bool formSaved;
    QLabel* mousePosLabel;
    QLabel* shapeLabel;
    QLabel* colorLabel;

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
	void radioSetRed();
	void radioSetGreen();
	void radioSetBlue();
	void radioSetSquare();
	void radioSetCircle();
	void radioSetTriangle();
	void getMouseLocation(int x, int y);

protected:
	void paintEvent(QPaintEvent* event);
	void leaveEvent(QEvent* event);

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
	QPainter* painter;

	QVBoxLayout *layout;

	QPen pen;
	QBrush brush;
	QPixmap pixmap;
	QRect rect;
};

#endif // IPACL_H
