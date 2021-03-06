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
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    SysInfo sysinfo;
    CPUInfo cpuinfo;

    int sorting_type = 2;
    QGridLayout *g = new QGridLayout();
    vector<QHBoxLayout*> h;
    vector<QLabel*> l_name ;
    vector<QLabel*> l_threads ;
    vector<QLabel*> l_RAM;
    vector<QLabel*> l_pid ;
    vector<QLabel*> l_user ;
    vector<QLabel*> l_cmdline ;
    vector<bool> allow_deleting_process;

    vector<QLabel*> cpulabels;
    vector<QProgressBar*> cpus;
    void load_processes_into_labels();
    void clear_labels_and_window(int number);
    void load_labels_into_window();
    void refresh_process_list();
    void refresh_cpu();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
