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

    QPixmap window_pic("/home/tony/projects/TaskManagerSPOVM/window_icon.png");
    QIcon window_icon(window_pic);
    this->setWindowIcon(window_icon);

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
   QPixmap pic_delete("/home/tony/projects/TaskManagerSPOVM/close_process.png");
   QIcon icon_delete(pic_delete);
   ui->pushButton_3->setIcon(icon_delete);
   QPixmap pic_create("/home/tony/projects/TaskManagerSPOVM/create_process.png");
   QIcon icon_create(pic_create);
   ui->pushButton->setIcon(icon_create);

   load_processes_into_labels();
   load_labels_into_window();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_processes_into_labels(){
     uint i = 0;
     vector<bool> allow_to_push;
     allow_to_push.resize(sysinfo.get_process_array().size());
     for(i = 0; i < allow_to_push.size(); i++){
       allow_to_push[i] = true;
     }
     i = 0;
     while(i != sysinfo.get_process_array().size()) {
         bool permission = true;
         QLabel *ll_threads = new QLabel();
         QLabel *ll_RAM = new QLabel();
         QLabel *ll_pid = new QLabel();
         QLabel *ll_user = new QLabel();
         QLabel *ll_cmdline = new QLabel();
         QLabel *ll_name = new QLabel();

         switch(sorting_type) {
         case 1:{
             ll_name->setText(sysinfo.get_process_array()[i].get_name().c_str());
             ll_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[i].get_mem()).c_str());
             ll_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[i].get_pid()).c_str());
             ll_user->setText(sysinfo.get_process_array()[i].get_user().c_str());
             ll_cmdline->setText(sysinfo.get_process_array()[i].get_cmdline().c_str());
             ll_threads->setText(TextTransit::itoa(sysinfo.get_process_array()[i].get_threads()).c_str());
             break;
         }
         case 2: {
             int min_pos;
             int min_RAM = 0;
             for(uint j = 0; j < sysinfo.get_process_array().size(); j++){
                 if((sysinfo.get_process_array()[j].get_mem() >= min_RAM) && (allow_to_push[j] == true)){
                 min_RAM = sysinfo.get_process_array()[j].get_mem();
                 min_pos = j;
                    }
                }
                allow_to_push[min_pos] = false;
                ll_name->setText(sysinfo.get_process_array()[min_pos].get_name().c_str());
                ll_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[min_pos].get_mem()).c_str());
                ll_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_pid()).c_str());
                ll_user->setText(sysinfo.get_process_array()[min_pos].get_user().c_str());
                ll_cmdline->setText(sysinfo.get_process_array()[min_pos].get_cmdline().c_str());
                ll_threads->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_threads()).c_str());
             break;
         }
         case 3: {
             int min_pos;
             string max_name = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
             for(uint j = 0; j < sysinfo.get_process_array().size(); j++){
                 int k = 0;
                 while(1) {
                 if((sysinfo.get_process_array()[j].get_name()[k] < max_name[k]) && (allow_to_push[j] == true)){
                    max_name = sysinfo.get_process_array()[j].get_name();
                    min_pos = j;
                    break;
                    }
                 if((sysinfo.get_process_array()[j].get_name()[k] > max_name[k]) || (allow_to_push[j] == false))
                 break;
                 k++;
                 }
             }
                allow_to_push[min_pos] = false;
                ll_name->setText(sysinfo.get_process_array()[min_pos].get_name().c_str());
                ll_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[min_pos].get_mem()).c_str());
                ll_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_pid()).c_str());
                ll_user->setText(sysinfo.get_process_array()[min_pos].get_user().c_str());
                ll_cmdline->setText(sysinfo.get_process_array()[min_pos].get_cmdline().c_str());
                ll_threads->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_threads()).c_str());
            break;
         }

         case 4: {
             int min_pos;
             int min_threads = 0;
             for(uint j = 0; j < sysinfo.get_process_array().size(); j++){
                 if((sysinfo.get_process_array()[j].get_threads() >= min_threads) && (allow_to_push[j] == true)){
                    min_threads = sysinfo.get_process_array()[j].get_threads();
                    min_pos = j;
                    }
                 }
                allow_to_push[min_pos] = false;
                ll_name->setText(sysinfo.get_process_array()[min_pos].get_name().c_str());
                ll_RAM->setText(TextTransit::itomem(sysinfo.get_process_array()[min_pos].get_mem()).c_str());
                ll_pid->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_pid()).c_str());
                ll_user->setText(sysinfo.get_process_array()[min_pos].get_user().c_str());
                ll_cmdline->setText(sysinfo.get_process_array()[min_pos].get_cmdline().c_str());
                ll_threads->setText(TextTransit::itoa(sysinfo.get_process_array()[min_pos].get_threads()).c_str());
             break;
         }
         }
         allow_deleting_process.push_back(permission);
         l_name.push_back(ll_name);
         l_RAM.push_back(ll_RAM);
         l_pid.push_back(ll_pid);
         l_user.push_back(ll_user);
         l_cmdline.push_back(ll_cmdline);
         l_threads.push_back(ll_threads);
     i++;
     }
}

void MainWindow::load_labels_into_window(){
    for(uint i = 0; i < sysinfo.get_process_array().size(); i++) {
        QHBoxLayout *hh = new QHBoxLayout();
        hh->addWidget(l_name[i]);
        hh->addWidget(l_RAM[i]);
        hh->addWidget(l_pid[i]);
        hh->addWidget(l_threads[i]);
        hh->addWidget(l_user[i]);
        h.push_back(hh);
        g->addLayout(h[i],i,1);
    }
    ui->scrollContents->setLayout(g);
}


void MainWindow::refresh_process_list() {
    int number = sysinfo.get_process_array().size();
    sysinfo.delete_process_array();
    sysinfo.refresh_process_array();
    clear_labels_and_window(number);
    load_processes_into_labels();
    load_labels_into_window();
}

void MainWindow::refresh_cpu() {
    cpuinfo.refresh_info();
    ui->progressBar->setValue(100*cpuinfo.get_totalRAM_usage()/cpuinfo.get_totalRAM());
    for(int i = 0; i < cpuinfo.get_cpu_num(); i++) {
       cpus[i]->setValue(cpuinfo.get_single_cpu_usage(i));
    }
}

void MainWindow::clear_labels_and_window(int number) {

    for(int i = number - 1; i >= 0; i--) {
        allow_deleting_process[i] = true;
        l_name[i]->clear();
        l_RAM[i]->clear();
        l_pid[i]->clear();
        l_user[i]->clear();
        l_cmdline[i]->clear();
        l_threads[i]->clear();

        allow_deleting_process.pop_back();
        l_name.pop_back();
        l_RAM.pop_back();
        l_pid.pop_back();
        l_user.pop_back();
        l_cmdline.pop_back();
        l_threads.pop_back();
        h.pop_back();
    }
}

void MainWindow::on_pushButton_clicked()
{
    string str;
    //str += "nohup ";
    str += ui->lineEdit->text().toStdString();
    //str += " &";
    if(system(str.c_str()) == 0) {
        ui->label_17->setStyleSheet("QLabel { color : Blue; }");
        ui->label_17->setText("Процесс успешно запущен");
        return;
    }
    ui->label_17->setStyleSheet("QLabel { color : Red; }");
    ui->label_17->setText("Неверное имя процесса");
    return;

}

void MainWindow::on_pushButton_2_clicked() {
     refresh_process_list();
}

void MainWindow::on_pushButton_3_clicked() {
    ui->label_17->setStyleSheet("QLabel { color : Red; }");
    ui->label_17->setText("");
    string str;
    str = ui->lineEdit->text().toStdString();
    if(!str.size()) ui->label_17->setText("Ошибка! Введите идентификатор процесса");
    for(uint i = 0; i < str.size(); i++) {
        if((str[i] > '9') || (str[i] < '0')) {
        for(uint j = 0; j < sysinfo.get_process_array().size(); j++) {
           if(l_name[j]->text().toStdString() == str) {
               if(l_name[j]->text().toStdString() == "systemd") {
                              ui->label_17->setText("Удаление этого процесса небезопасно");
                              return;
                          }
               if(!allow_deleting_process[j]){
                   ui->label_17->setStyleSheet("QLabel { color : Blue; }");
                   ui->label_17->setText("Процесс уже удален");
                   return;
               }
               int pid = TextTransit::atoi(l_pid[j]->text().toStdString());
               l_name[j]->setStyleSheet("QLabel { color : Red; }");
               l_pid[j]->setStyleSheet("QLabel { color : Red; }");
               l_RAM[j]->setStyleSheet("QLabel { color : Red; }");
               l_threads[j]->setStyleSheet("QLabel { color : Red; }");
               l_user[j]->setStyleSheet("QLabel { color : Red; }");
               ui->label_17->setStyleSheet("QLabel { color : Blue; }");
               ui->label_17->setText("Процесс успешно удален");
               allow_deleting_process[j] = false;
               kill(pid,9);
               return;
           }
        }
        ui->label_17->setText("Ошибка! Не существует процесса с таким id/именем");
        return;
        }
    }
    int pid = TextTransit::atoi(str);

    for(uint i = 0; i < sysinfo.get_process_array().size(); i++) {

        if(sysinfo.get_process_array()[i].get_pid() == pid) {
            if(!allow_deleting_process[i]){
                ui->label_17->setStyleSheet("QLabel { color : Blue; }");
                ui->label_17->setText("Процесс уже удален");
                return;
            }

            for(uint j = 0; j < sysinfo.get_process_array().size(); j++) {
                if(l_pid[j]->text().toStdString() == TextTransit::itoa(pid)){
                    if(l_name[j]->text().toStdString() == "systemd") {
                                   ui->label_17->setText("Удаление этого процесса небезопасно");
                                   return;
                               }
                    l_name[j]->setStyleSheet("QLabel { color : Red; }");
                    l_pid[j]->setStyleSheet("QLabel { color : Red; }");
                    l_RAM[j]->setStyleSheet("QLabel { color : Red; }");
                    l_threads[j]->setStyleSheet("QLabel { color : Red; }");
                    l_user[j]->setStyleSheet("QLabel { color : Red; }");
                    ui->label_17->setStyleSheet("QLabel { color : Blue; }");
                    ui->label_17->setText("Процесс успешно удален");
                    allow_deleting_process[i] = false;
                    kill(pid,9);
                    return;
                    }
                }
            }
    }
    ui->label_17->setText("Ошибка! Нет процесса с таким id/именем");
    return;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1.toStdString() == "Идентификатор") sorting_type = 1;
    if(arg1.toStdString() == "Загрузка RAM") sorting_type = 2;
    if(arg1.toStdString() == "Имя") sorting_type = 3;
    if(arg1.toStdString() == "К-во потоков") sorting_type = 4;
}
