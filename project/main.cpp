
#include "mainwindow.h"
#include "historyitem.h"
#include "alignment.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
