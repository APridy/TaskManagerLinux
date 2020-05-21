#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include "texttransit.h"
#include "cpuinfo.h"
#include "sysinfo.h"
#include "process.h"
#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

namespace Ui {
class MainWindow;
//class CPUInfo;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SysInfo sysinfo;
    CPUInfo cpuinfo;
    //vector<QLabel> labels;
   // vector<QProgressBar> cpus;
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    //Ui::CPUInfo *cpuinfo;
};

#endif // MAINWINDOW_H
