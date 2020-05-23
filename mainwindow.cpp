#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_3->setText(cpuinfo.get_model().c_str());
    ui->label_5->setText(TextTransit::itoa(cpuinfo.get_cpu_num()).c_str());
    ui->label_7->setText(TextTransit::itomem(cpuinfo.get_totalRAM()).c_str());
    ui->progressBar->setValue(100*cpuinfo.get_totalRAM_usage()/cpuinfo.get_totalRAM());
    ui->verticalLayoutWidget_4->setMaximumSize(400,48*cpuinfo.get_cpu_num());

    cpulabels.resize(cpuinfo.get_cpu_num());
    cpus.resize(cpuinfo.get_cpu_num());

    for(int i = 0; i < cpuinfo.get_cpu_num(); i++) {
       QLabel *l = new QLabel();
       QProgressBar *b = new QProgressBar();
       string str = "Ядро №" + TextTransit::itoa(i + 1);
       l->setText(str.c_str());
       b->setValue(cpuinfo.get_single_cpu_usage(i));
       cpulabels[i] = l;
       cpus[i] = b;
       ui->verticalLayout_4->addWidget(cpulabels[i]);
       ui->verticalLayout_4->addWidget(cpus[i]);
    }

   load_processes_into_labels();
   load_labels_into_window();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_processes_into_labels(){
     QPixmap pic("/home/tony/projects/TaskManagerSPOVM/close_process.png");
     QIcon icon(pic);
     for(int i = 0; i < sysinfo.get_process_array().size(); i++) {
         QLabel *ll_threads = new QLabel();
         QLabel *ll_RAM = new QLabel();
         QLabel *ll_pid = new QLabel();
         QLabel *ll_user = new QLabel();
         QLabel *ll_cmdline = new QLabel();
         QPushButton *ccls = new QPushButton();
         QPushButton *ccmd = new QPushButton();
         QLabel *ll_name = new QLabel();
         ll_name->setText(sysinfo.get_process_array()[i].get_name().c_str());
         ll_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[i].get_mem()).c_str());
         ll_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[i].get_pid()).c_str());
         ll_user->setText(sysinfo.get_process_array()[i].get_user().c_str());
         ll_cmdline->setText(sysinfo.get_process_array()[i].get_cmdline().c_str());
         ll_threads->setText(TextTransit::itoa(sysinfo.get_process_array()[i].get_threads()).c_str());
         ccmd->setMaximumSize(36,22);
         ccmd->setText("CMD");
         ccls->setMaximumSize(20,20);
         ccls->setIcon(pic);
         l_name.push_back(ll_name);
         l_RAM.push_back(ll_RAM);
         l_pid.push_back(ll_pid);
         l_user.push_back(ll_user);
         l_cmdline.push_back(ll_cmdline);
         l_threads.push_back(ll_threads);
         cmd.push_back(ccmd);
         cls.push_back(ccls);
     }
}

void MainWindow::load_labels_into_window(){
    for(int i = 0; i < sysinfo.get_process_array().size(); i++) {
        QHBoxLayout *hh = new QHBoxLayout();
        hh->addWidget(l_name[i]);
        hh->addWidget(l_RAM[i]);
        hh->addWidget(l_pid[i]);
        hh->addWidget(l_threads[i]);
        hh->addWidget(l_user[i]);
        hh->addWidget(cmd[i]);
        hh->addWidget(cls[i]);
        h.push_back(hh);
        g->addLayout(h[i],i,1);
    }
    ui->scrollContents->setLayout(g);
}


void MainWindow::refresh_window() {
   // sysinfo.refresh_process_array();
    cpuinfo.refresh_info();
    ui->progressBar->setValue(100*cpuinfo.get_totalRAM_usage()/cpuinfo.get_totalRAM());
    for(int i = 0; i < cpuinfo.get_cpu_num(); i++) {
       cpus[i]->setValue(cpuinfo.get_single_cpu_usage(i));
    }

}

void MainWindow::clear_labels_and_window() {
    string j = "0";

    for(int i =  sysinfo.get_process_array().size() - 1; i >= 0; i--) {
        l_name[i]->clear();
        l_RAM[i]->clear();
        l_pid[i]->clear();
        l_user[i]->clear();
        l_cmdline[i]->clear();
        l_threads[i]->clear();

        h[i]->removeWidget(cmd[i]);
        h[i]->removeWidget(cls[i]);

        l_name.pop_back();
        l_RAM.pop_back();
        l_pid.pop_back();
        l_user.pop_back();
        l_cmdline.pop_back();
        l_threads.pop_back();
        cmd.pop_back();
        cls.pop_back();
        h.pop_back();
    }
    l_name.clear();

}

void MainWindow::on_pushButton_clicked()
{
    refresh_window();
}

void MainWindow::on_pushButton_2_clicked()
{
    clear_labels_and_window();
}
