#include "ipacl.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IPACL w;
    w.show();
    return a.exec();
}
