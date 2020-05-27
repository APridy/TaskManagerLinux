#ifndef INFOUPDATERTHREAD_H
#define INFOUPDATERTHREAD_H
#include <QThread>
#include <mainwindow.h>

class InfoUpdaterThread : public QThread
{
public:
    explicit InfoUpdaterThread(QString threadName,MainWindow *window);
    MainWindow *w;
private:
    QString name;
    void run();
};

#endif // INFOUPDATERTHREAD_H
