#include "sendfilethread.h"
#include <unistd.h>
#include <QDebug>
SendFileThread::SendFileThread(QObject *parent):QThread(parent)
{

}
SendFileThread::~SendFileThread()
{

}
void SendFileThread::run()
{
    while(1)
    {
        qDebug()<<"hello";
        sleep(1);
    }
}

