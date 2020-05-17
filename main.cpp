#include "mainwindow.h"
#include "sysinfo.h"
#include <QApplication>
#include <QLabel>
#include <sys/stat.h>
#include <string>
#include <stdio.h>
#include <sys/mount.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <math.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <cpuinfo.h>
//#include <fstream.h>


using namespace std;

string result;

int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);
   // MainWindow w;




    SysInfo sysinfo;
    CPUInfo cpuinfo;
    //sysinfo.print_processes();
    cpuinfo.refresh_info(sysinfo);
    cpuinfo.print_info();
    //w.show();

   // return a.exec();

}
