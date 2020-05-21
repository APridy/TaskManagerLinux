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
    cpuinfo.refresh_info(sysinfo);
    ui->label_3->setText(cpuinfo.get_model().c_str());
    ui->label_5->setText(TextTransit::itoa(cpuinfo.get_cpu_num()).c_str());
    ui->label_7->setText(TextTransit::itomem(cpuinfo.get_totalRAM()).c_str());
    ui->progressBar->setValue(100*cpuinfo.get_totalRAM_usage()/cpuinfo.get_totalRAM());
    //ui->verticalLayout_4->count() = 4;
    ui->verticalLayoutWidget_4->setMaximumSize(400,48*cpuinfo.get_cpu_num());

//    ui->comboBox->addItem("Идентификатор");
//    ui->comboBox->addItem("Загрузка RAM");
//    ui->comboBox->addItem("Имя процесса");
//    ui->comboBox->addItem("Количество потоков");

    for(int i = 0; i < cpuinfo.get_cpu_num(); i++) {
       //QLabel *l = qobject_cast<QLabel*>(ui->verticalLayout_4->itemAt(i)->widget());
       QLabel *l = new QLabel();
       QProgressBar *b = new QProgressBar();

       string str = "Ядро №" + TextTransit::itoa(i + 1);
       l->setText(str.c_str());
       b->setValue(cpuinfo.get_single_cpu_usage(i));

       ui->verticalLayout_4->addWidget(l);
       ui->verticalLayout_4->addWidget(b);
       //gobject_cast<QLabel>(ui->verticalLayout_4->itemAt(i)->widget())
       //QDynamicButton *button = qobject_cast<QDynamicButton*>(ui->verticalLayout_4->itemAt(i)->widget());
       // labels.push_back(l);
    }
    QGridLayout *g = new QGridLayout();

    for(int i = 0; i < sysinfo.get_process_array().size(); i++) {
       QPixmap pic("/home/tony/projects/TaskManagerSPOVM/close_process.png");
       QIcon icon(pic);
       QHBoxLayout *h = new QHBoxLayout();
       QLabel *l_name = new QLabel();
       QLabel *l_RAM = new QLabel();
       QLabel *l_pid = new QLabel();
       QLabel *l_user = new QLabel();
       QLabel *l_cmdline = new QLabel();
       QPushButton *cls = new QPushButton();
       QPushButton *cmd = new QPushButton();


       l_name->setText(sysinfo.get_process_array()[i].get_name().c_str());
       l_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[i].get_mem()).c_str());
       l_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[i].get_pid()).c_str());
       l_user->setText(sysinfo.get_process_array()[i].get_user().c_str());
       l_cmdline->setText(sysinfo.get_process_array()[i].get_cmdline().c_str());
       cmd->setMaximumSize(36,22);
       cmd->setText("CMD");
       cls->setMaximumSize(20,20);
       cls->setIcon(pic);
      // cls->setIconSize(pic.rect().size());

       h->addWidget(l_name);
       h->addWidget(l_RAM);
       h->addWidget(l_pid);
       h->addWidget(l_user);
       h->addWidget(cmd);
       h->addWidget(cls);
     //  h->addWidget(l_cmdline);

       g->addLayout(h,i,1);
    }
    ui->scrollContents->setLayout(g);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

}
