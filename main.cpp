#include "mainwindow.h"
#include <QApplication>
/*este es el archivo main.cpp*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
