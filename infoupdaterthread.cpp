#include "infoupdaterthread.h"
#include <QDebug>


InfoUpdaterThread::InfoUpdaterThread(QString threadName,MainWindow *window) :
     name(threadName)
{
    w = window;
}

void InfoUpdaterThread::run()
{
    while(1) {
    qDebug() << name;
    w->refresh_cpu();
    }
}
