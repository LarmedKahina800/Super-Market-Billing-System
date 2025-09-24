#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    std::ofstream out("Bill.txt", std::ofstream::trunc); // trunc = overwrite
    out.close();

    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Supermarket Billing System");
    w.resize(600, 400);
    w.show();

    return a.exec();
}
