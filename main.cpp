#include "mainwindow.h"
#include "sysinfo.h"
#include "cpuinfo.h"
#include <QApplication>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <infoupdaterthread.h>


using namespace std;

string result;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    InfoUpdaterThread info_updater("InfoUpdater", &w);
    info_updater.start();
    return a.exec();
}
