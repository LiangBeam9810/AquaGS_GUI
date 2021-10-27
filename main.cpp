#include "mainwindow.h"
#include <QApplication>

extern MainWindow* m;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    m = &w;
    w.show();

    return a.exec();
}

