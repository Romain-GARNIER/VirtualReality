#include "rvwidget.h"

#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tuto1.2");
    w.show();
    return a.exec();
}
