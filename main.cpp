#include "mainwindow.h"
#include "sysinfo.h"
#include "cpuinfo.h"
#include <QApplication>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>



using namespace std;

string result;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
